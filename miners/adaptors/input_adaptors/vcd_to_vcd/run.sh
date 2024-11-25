in_path=$1
out_path=$2

if [ -z "$in_path" ] || [ -z "$out_path" ]; then
    echo "Usage: run.sh <in_path> <out_path>"
    exit 1
fi


cp -r $in_path $out_path
