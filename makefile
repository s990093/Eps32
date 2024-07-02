.PHONY: git run

SERIAL_PORT := /dev/tty.usbserial-110

git:
	git add .
	git commit -m "New commit"
	git push

run:
	python run.py --serial-port=$(SERIAL_PORT)
