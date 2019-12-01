let acc=0

while IFS=" " read -a mass
do
	let fuel="${mass[@]}/3-2"
	let acc=$acc+$fuel
done

echo $acc
