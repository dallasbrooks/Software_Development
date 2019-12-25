import sys
import re
import string

#get html from stdin()
def get_html():
	raw_html = ""
	for line in sys.stdin:
		raw_html += line.rstrip().strip()  
	return raw_html

#convert html into a table
def convert_html(raw_html):
	csv = re.split(r"</table[^>]*>", raw_html, flags = re.IGNORECASE)
	csv = [re.sub(r"<br[^>]*>\s*", "", table, flags = re.IGNORECASE) for table in csv]
	return [table for table in csv if len(table) > 0]

#print each table in csv format
def print_csv(csv):
	for index in range(len(csv)):
		if(index):
			print()
		rows = re.split(r"</tr[^>]*>", csv[index], flags = re.IGNORECASE)
		rows = [re.sub(r"<tr[^>]*>\s*", "", row, flags = re.IGNORECASE) for row in rows if len(row)]
		print("TABLE {}:".format(index+1))
		rows = [re.split(r"</t[^>]*>", row, flags = re.IGNORECASE) for row in rows]
		rows = [[data for data in row if len(data)] for row in rows]
		rows = [[re.sub(r"<t[^>]*>\s*", "", data, flags = re.IGNORECASE) for data in row] for row in rows]
		max_len = len(max(rows, key=len))
		for row in rows:
			print_csv_row(row, max_len)

#print each csv row from table
def print_csv_row(row, ensure_cells):
	row = [re.sub(r"\s+", " ", word) for word in row]
	row += ["" for index in range(ensure_cells - len(row))]
	print(",".join(row))           

def main():
	if(sys.stdin.isatty()):
		print("Failure: no given file")
		return -1
	raw_html = get_html()
	csv = convert_html(raw_html)
	print_csv(csv)

main()
#run with python3 table_to_csv.py < <input_file.html>