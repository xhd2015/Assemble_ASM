
need_sync_dir := for_copy_from_document
from_dir	:= ~/Documents/BIOS

.PHONY: sync_dir

.ONESHELL:
sync_dir:
	@
	echo 'deleting(*old*): '$(need_sync_dir)'/* ...'
	cd $(need_sync_dir)
	rm -Rf *
	echo 'copying from '$(from_dir)'(*new*) ...'
	cp -R $(from_dir) -t .
	echo 'sync done.'

