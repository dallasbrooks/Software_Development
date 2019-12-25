import sys
import os
import re

#find all delay times for selected departure and return average delay
def find_delay(data, departure, delay, n):
	for a in range(18, len(data), 18):
		if(data[a] == departure):
			actual_departure = int(data[a+11]) * 60 + int(data[a+12])
			schelduled_departure = int(data[a+6]) * 60 + int(data[a+7])
			delay += actual_departure - schelduled_departure
			n += 1
	return float(delay)/n, n

#print the results for selected departure
def print_delay(departure, month, delay): 
	print("RESULTS")
	print("{0}:".format(departure))
	if(delay == 0):
		print("    No delay data for {0}".format(month))
	else:
		print("    Average delay for {0}: {1:.2f}".format(month, delay))
	print("END")

def main():
	for a in range(len(sys.argv)):
		if(len(sys.argv) == 1):
			print("Failure: no input data")
			return -1
		if(not os.path.exists(sys.argv[a])):
			print("Failure: could not access file")
			return -1
	departure = ""
	while(departure != "q"):
		departure = input("Departing from Tsawwassen (t) or Swartz Bay (s)? ")
		if(departure == "t"):
			departure = "Tsawwassen"
			break
		if(departure == "s"):
			departure = "Swartz Bay"
			break
		if(departure == "q"):
			print("Quitting program")
			return -1
		print("Please try again. (\"q\" for quit)")
	month_index = ""
	while(month_index != "q"):
		month_index = input("Month of departure (1,2,3,4,5,6,7,8,9,10,11,12)? ")
		if(month_index.isdigit()):
			month_index = int(month_index)
			if(month_index > 0 and month_index < 13):
				break
		if(month_index == "q"):
			print("Quitting program")
			return -1
		print("Please try again. (\"q\" for quit)")
	delay = 0
	n = 0
	for a in range(1, len(sys.argv), 1):
		if(os.path.exists(sys.argv[a])):
			all_data = open(sys.argv[a]).read()
			data = re.split(",|\n", all_data)
			if(month_index == int(data[22])):
				delay, n = find_delay(data, departure, delay, n)
	month_list = ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"]
	month = month_list[month_index-1]
	print_delay(departure, month, delay)
	main()
	
main()
#run with python3 ferry_delays.py <dataset1.csv> [dataset2.csv ... datasetN.csv]