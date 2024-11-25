input=$1    
output=$2

if [ -z "$input" ] || [ -z "$output" ]; then
    echo "Usage: $0 <input> <output>"
    exit 1
fi

./harm --clk clk --conf /input/generic.xml --vcd /input/t1.vcd --vcd-ss arb2_tb --dump-to /output
