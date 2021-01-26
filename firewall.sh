#!/bin/bash

rules_txt="$1"


if [[ -e legit_rules.txt ]]; then
	rm legit_rules.txt
fi
if [[ -e packetsss.txt ]]; then
	rm packetsss.txt
fi

if [[ -e print_shit_out.txt ]]; then
	rm print_shit_out.txt
fi

#insert stdin to file packetsss.txt
cat > packetsss.txt



grep -o '^[^#]*' $rules_txt > legit_rules.txt

cat legit_rules.txt | sort | uniq > legit_rules_uniq.txt

while read line; do
	IFS=',' read -r -a fields <<< "$line"
	
data=$(cat packetsss.txt | \
       ./firewall.exe "${fields[0]}" 2>/dev/null | \
       ./firewall.exe "${fields[1]}" 2>/dev/null| \
       ./firewall.exe "${fields[2]}" 2>/dev/null| \
       ./firewall.exe "${fields[3]}" 2>/dev/null)

echo "$data" >> temp.txt

done < legit_rules_uniq.txt


cat temp.txt | sort | uniq | tr -d " \t" 

rm -f temp.txt packetsss.txt legit_rules_uniq.txt legit_rules.txt



