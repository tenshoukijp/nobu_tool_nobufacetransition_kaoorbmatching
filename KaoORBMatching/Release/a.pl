my $result = system("KaoORBMatching.exe nobu12a.png nobu12b.png");
$result = $result >> 8;

if ($result == 2 ) {
	print("����v");
} elsif ($result == 1 ) {
	print("��v");
} elsif( $result==0) {
	print("�s��v");
} else {
	print("�G���[");
}