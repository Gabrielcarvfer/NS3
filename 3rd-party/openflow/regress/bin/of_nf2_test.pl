#!/usr/bin/perl -w

##############################################################################
#
# Wrapper for OpenFlow regression tests
# $Id: of_regress_test.pl 105 2008-06-06 04:07:05Z brandonh $
#
##############################################################################

use OF::Base;
use Test::RegressTest; 
use strict; 
use OF::OFUtil;

# check vars are set.
check_OF_vars_set();

sub INT_Handler {
	my $signame = shift;
	print "\nNo interrupt handler implemented yet...\n";
	print "\nExited with SIG$signame\n";
	exit(1);
}

my $of_port = get_of_port();
push @ARGV, "--root=$ENV{'OFT_ROOT'}", "--map=$ENV{'OFT_ROOT'}/bin/nf2.map", "--common-st-args=nf2", "--controller=localhost:$of_port", "--port_base=0";

run_regress_test( \&INT_Handler, @ARGV );
