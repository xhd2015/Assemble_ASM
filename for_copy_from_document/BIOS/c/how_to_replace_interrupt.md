
# inner interrupt do not increments the ip
When you write interrupt handler for some exception,you'd better know this.Because call will increment the ip for you,but interrupt does not do this.
So you may write:
	mov $0x1,%eax
	xor %ebx,%ebx
	div %ebx  ----- int0
If you replace int 0 with:
new_int0:
	cli
	....#do something to this exception
	iret  #!doesn't work,because iret pops the cs:ip,which points to the original int0!
	      #!So this is actually a trailing recursive call,or an infinite loop!

# however , external interrupt increments it,so int 0 works
	int $0x0  #!WORKS!IP autoincrement
