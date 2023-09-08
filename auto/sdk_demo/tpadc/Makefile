Target = tpadc_test

include ../makefile_cfg

all: $(Target)
	$(CC) tpadc_test.c -o $(Target)
	@cp -f $(Target) $(INSTATLL_PATH)
	@echo "generate  $(Target) success!!!"

.PHONY:clean cleanall

clean:
	@rm -f  $(Target)
