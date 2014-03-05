        .device p17c

start:
	tablrd 0, 0, 0xff
	tablrd 0, 1, 0x10
	tablrd 1, 0, 0x10
	tablrd 1, 1, 0x10

	tablwt 0, 0, 0xff
	tablwt 0, 1, 0xff
	tablwt 1, 0, 0x10
	tablwt 1, 1, 0x10
