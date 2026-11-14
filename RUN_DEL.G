foreach i { *.o *.tos }
	if { -f $i }
		echo Rm $i
		Rm $i
	endif
endfor
