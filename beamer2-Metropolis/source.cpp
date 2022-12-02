case etSQLESCAPE3: { /* %w: Escape " characters */
	char q = '"';    /* Quote character */
	int32_t quoteNum;      /* Number of Quote Character */
	char *escarg = input; /* escarg points to the input string*/
	
	int32_t k = -1;
	for(i=quoteNum=0; k!=0 && (ch=escarg[i]/*[1]*/)!=0; i++, k--){
		if( ch==q )
			quoteNum++;
		if( (ch&0xc0) == 0xc0 ){
			while( (escarg[i+1]/*[2]*/ & 0xc0)==0x80 ){ i++; }
		}
	}

	int32_t numOfChars = i;
	int32_t n = quoteNum + numOfChars + 3; /*length of output*/
	if( n > etBUFSIZE ){
		bufpt = zExtra = printfTempBuf(pAccum, n);
		if( bufpt==0 ) return;
	}else{
		bufpt = buf; // buf is on the stack
	}

	for( s=i=0; i < numOfChars; i++ ){
		bufpt[s++] = ch = escarg[i];
		if( ch==q ) bufpt[s++] = ch;
	}
	bufpt[s] = 0;
	goto adjust_width_for_utf8;
}
