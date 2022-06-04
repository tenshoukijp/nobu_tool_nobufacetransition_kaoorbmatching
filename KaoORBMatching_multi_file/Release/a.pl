my $result = system("KaoORBMatching.exe nobu12a.png nobu12b.png");
$result = $result >> 8;

if ($result == 2 ) {
	print("’´ˆê’v");
} elsif ($result == 1 ) {
	print("ˆê’v");
} elsif( $result==0) {
	print("•sˆê’v");
} else {
	print("ƒGƒ‰[");
}