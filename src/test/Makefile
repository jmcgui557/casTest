all:
	$(MAKE) -f testSuiteMakefile.mak $@
	$(MAKE) -f casTestSelf.mak $@
	$(MAKE) -f skipTest.mak $@
	$(MAKE) -f testSummaryTest.mak $@

%:
	$(MAKE) -f testSuiteMakefile.mak $@
	$(MAKE) -f casTestSelf.mak $@
	$(MAKE) -f skipTest.mak $@
	$(MAKE) -f testSummaryTest.mak $@
