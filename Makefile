SUBDIRS = \
	Common \
	Dummy \
	Dummy_Hub_Client \
	Hub \
	Manager \

all: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ 

.PHONY: all $(SUBDIRS)
