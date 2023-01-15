Using UNIX signals to send text between processes

Example Shell session (annotated with comments after "#"):

	$ make
	$ ./server &
	13170 # Server prints its PID.
	$ ./client \
		`# Client takes server's PID as the first argument:` \
		13170 \
		`# And some message as the second argument:` \
		hello!
	hello!$ # Note: newline is not printed.
	$ # Server just prints what it got.
	$ # If we want to print a newline, we need to do some work (because shell substitution removes trailing new lines).
	$ ./client \
		13170 \
		"$(printf hello\\n\\1)" \
		# Will display as hello followed by a new line (hack).

License: MIT.
