#!/usr/bin/perl -w
# test_forward_exact_all

use strict;
use OF::Includes;

sub forward_all {

	forward_simple(@_, 'all');
}

sub my_test {

	my ( $sock, $options_ref ) = @_;

	enable_flow_expirations( $ofp, $sock );

	for_all_ports( $ofp, $sock, $options_ref, \&forward_all, 0x0);
}

run_black_box_test( \&my_test, \@ARGV );