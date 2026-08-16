BASENAME  := conker
VERSION   := us

BUILD_DIR  = build
TARGET     = $(BUILD_DIR)/$(BASENAME).$(VERSION)
GAME_DIR   = $(BASENAME)

BIN_DIR    = assets

ifeq ($(VERSION),ects)
BIN_FILES  = $(wildcard $(BIN_DIR)/*.bin)
else
# don't compile game.$(VERSION).bin
BIN_FILES  = $(filter-out $(BIN_DIR)/game.$(VERSION).bin, $(wildcard $(BIN_DIR)/*.bin))
endif

EXTRACT_DIR = extracted

RZIP_DIRS  = $(wildcard $(BIN_DIR)/rzip/assets*)
RZIP_FILES = $(wildcard $(BIN_DIR)/rzip/assets*/assets*.bin)

O_FILES    = $(foreach file,$(BIN_FILES) $(RZIP_FILES),$(BUILD_DIR)/$(file:.bin=.bin.o))

# The asset blobs that "make -C $(GAME_DIR) replace" overwrites are the ONLY outputs of
# the inner (code) build; everything else under $(BIN_DIR)/ comes from baserom extraction.
# They are the join point between the two builds, and therefore where the outer build has
# to take its dependency on the inner one.
ifeq ($(VERSION),ects)
GAME_CODE_BIN = $(BIN_DIR)/game.$(VERSION).bin
else
GAME_CODE_BIN = $(BIN_DIR)/game.$(VERSION).rzip.bin
endif

GAME_CODE_BINS = $(BIN_DIR)/header.$(VERSION).bin \
                 $(BIN_DIR)/boot.$(VERSION).bin \
                 $(BIN_DIR)/init.$(VERSION).bin \
                 $(BIN_DIR)/debugger.$(VERSION).bin \
                 $(GAME_CODE_BIN)

GAME_CODE_O_FILES = $(foreach file,$(GAME_CODE_BINS),$(BUILD_DIR)/$(file:.bin=.bin.o))

INNER_BIN  = $(GAME_DIR)/$(BUILD_DIR)/$(BASENAME).$(VERSION).bin
INNER_SHA1 = $(GAME_DIR)/$(BASENAME).$(VERSION).sha1

CROSS   = mips-linux-gnu-
CPP     = cpp
LD      = $(CROSS)ld
OBJCOPY = $(CROSS)objcopy
PYTHON  = python3

LD_SCRIPT = $(BASENAME).ld
LDFLAGS   = -T $(BUILD_DIR)/$(LD_SCRIPT) -Map $(TARGET).map --no-check-sections

ifeq ($(NON_MATCHING),1)
VERIFY :=
else
VERIFY := verify
endif

### Targets

default: all

all: dirs $(TARGET).z64 $(VERIFY)

dirs:
	$(foreach dir,$(BIN_DIR) $(RZIP_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))

clean:
	rm -rf build

really-clean: clean
	rm -rf assets
	rm -rf rzip
	make -C $(GAME_DIR) really-clean

check: .baserom.$(VERSION).ok

extract: check $(GAME_DIR)/$(BASENAME).$(VERSION).bin

decompress: $(EXTRACT_DIR)/00000000.bin

verify: $(TARGET).z64
	@echo "$$(cat $(INNER_SHA1))  $(INNER_BIN)" | sha1sum --check
	@echo "$$(cat $(BASENAME).$(VERSION).sha1)  $<" | sha1sum --check

### Recipes

$(BUILD_DIR)/$(LD_SCRIPT): $(LD_SCRIPT)
	$(CPP) -P -DBUILD_DIR=$(BUILD_DIR) -o $@ $<

$(TARGET).elf: $(O_FILES) $(BUILD_DIR)/$(LD_SCRIPT)
	@$(LD) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.bin.o: %.bin
	$(LD) -r -b binary -o $@ $<

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) $(OBJCOPYFLAGS) -O binary $< $@

$(TARGET).z64: $(TARGET).bin
	@cp $< $@

# Run the inner (code) build and refresh $(BIN_DIR)/ from it. Phony, so its recipe runs on
# every invocation and $(MAKE)'s exit status propagates: an inner build that fails to
# compile, or that is not byte-perfect (inner 'replace' is gated on inner 'verify'), aborts
# the outer build. The $(GAME_CODE_BIN) prerequisite forces the baserom extraction rule
# below to run FIRST when it is out of date, so split.py can never land on top of the
# blobs 'replace' just copied in.
.PHONY: game-code
game-code: $(GAME_CODE_BIN)
	$(MAKE) -C $(GAME_DIR) VERSION=$(VERSION) replace

# Rebuild the join-point objects after every inner build. This is what makes $(TARGET).z64
# -- and therefore 'verify' -- unreachable without a successful inner build in this same
# invocation. Deliberately no recipe: the $(BUILD_DIR)/%.bin.o pattern rule above supplies
# it, and the pattern's own %.bin prerequisite stays first, so $< is unaffected.
$(GAME_CODE_O_FILES): game-code

# combine
$(GAME_DIR)/$(BASENAME).$(VERSION).bin: $(BIN_DIR)/game.$(VERSION).bin
	cat $(BIN_DIR)/header.$(VERSION).bin $(BIN_DIR)/boot.$(VERSION).bin $(BIN_DIR)/init.$(VERSION).bin $(BIN_DIR)/game.$(VERSION).bin $(BIN_DIR)/debugger.$(VERSION).bin > $@

# game code is not compressed in ECTS ROM
ifeq ($(VERSION),ects)
$(BIN_DIR)/game.$(VERSION).bin: $(BASENAME).$(VERSION).yaml
	$(PYTHON) tools/n64splat/split.py $<
else
$(BIN_DIR)/game.$(VERSION).bin: $(BIN_DIR)/game/rzip/data/0000.bin
	cat $(BIN_DIR)/game/rzip/code/0*.bin $(BIN_DIR)/game/rzip/data/0000.bin > $@

$(BIN_DIR)/game/rzip/data/0000.bin: $(BIN_DIR)/game.$(VERSION).rzip.bin
	$(PYTHON) tools/n64splat/split.py game.$(VERSION).rzip.yaml --modes bin rzip

$(BIN_DIR)/game.$(VERSION).rzip.bin: $(BASENAME).$(VERSION).yaml
	$(PYTHON) tools/n64splat/split.py $<
endif

.baserom.$(VERSION).ok: baserom.$(VERSION).z64
	@echo "$$(cat $(BASENAME).$(VERSION).sha1)  $<" | sha1sum --check
	@touch $@

$(EXTRACT_DIR)/00000000.bin:
	@mkdir -p $(EXTRACT_DIR)
	$(PYTHON) tools/extract_compressed.py config/compressed.$(VERSION).yaml $(BIN_DIR)/compressed.bin $(EXTRACT_DIR)

# settings
.PHONY: all clean default dirs check extract decompress verify really-clean
SHELL = /bin/bash -e -o pipefail
