`define CS(ID,ORIGINAL,REPLACEMENT) \
`ifdef ID  \
    REPLACEMENT\
`else\
    ORIGINAL\
`endif
