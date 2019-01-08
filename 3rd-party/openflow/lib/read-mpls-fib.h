// MAH: start
#ifndef READ_MPLS_CONFIG_H
#define READ_MPLS_CONFIG_H 1

// read an XML file that specifies a FIB for an MPLS switch
mplsFibPtr read_mpls_fib(char *mpls_fib_file, struct mpls_switch *sw);

#endif
// MAH: end
