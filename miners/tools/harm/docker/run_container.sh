input_mount_volume=$1
output_mount_volume=$2
com=$3
docker run --rm -it -v $input_mount_volume:/input:rw -v $output_mount_volume:/output:rw samger/harm:latest $com