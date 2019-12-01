function calculate_fuel {
	let f="$1/3-2"
	if [ "$f" -gt 0 ]
	then
		let r="$f+$(calculate_fuel $f)"
		echo $r
	else
		echo "0"
	fi
}

let acc=0

while IFS=" " read -a mass
do
	let fuel="$(calculate_fuel ${mass[@]})"
	let acc="acc+fuel"
done

echo $acc
