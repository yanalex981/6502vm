/*
while !cpu.status.break

fetch
	get instruction
decode
	get decode function
	call decode function
		increment pc or branching won't work...
	get instruction function
execute
	call instruction function
increment pc
*/