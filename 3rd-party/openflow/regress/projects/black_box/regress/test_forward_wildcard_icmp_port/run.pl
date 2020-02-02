#!/usr/bin/perl -w
# test_forward_wildcard_icmp_port

use strict;
use OF::Includes;

sub forward_wc_port {
        forward_simple_icmp(@_, 'port', 0);  # 0: fool_flg = off
}

sub my_test {

	my ( $sock, $options_ref ) = @_;

	enable_flow_expirations( $ofp, $sock );
	for_all_wildcards( $ofp, $sock, $options_ref, \&forward_wc_port);
}

run_black_box_test( \&my_test, \@ARGV );


