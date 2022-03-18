from colorama import init, Fore, Back, Style
from dataclasses import dataclass
import os

init()

@dataclass
class USED:
	first: bool
	second: int
@dataclass
class CODE:
	a: str
	p: int
	q: str

used: list[USED] = []
arr: list[CODE] = []

def comp(x):
	return x.p

def clear():
	arr.clear()
	used.clear()
	for i in range(1200):
		used.append(USED(False, 0))

def input1(first_s):
	for i in range(len(first_s)):
		if used[ord(first_s[i])].first == False:
			used[ord(first_s[i])].first = True

			if len(arr) != 0:
				used[ord(first_s[i])].second = len(arr)

			arr.append(CODE(first_s[i], 1, ""))
		else:
			arr[used[ord(first_s[i])].second].p += 1

	arr.sort(key=comp, reverse=True)

	for i in range(len(arr)):
		used[ord(arr[i].a)].second = i

def makefano(begin, end):
	if end - begin == 1:
		return

	minabs, minpos, left, right = -1, -1, 0, 0

	for i in range(begin, end):
		right += arr[i].p

	for i in range(begin, end):
		if abs(left - right) < minabs or minabs == -1:
			minabs = abs(left - right)
			minpos = i

		left += arr[i].p
		right -= arr[i].p

	for i in range(minpos, end):
		arr[i].q += '0'
	for i in range(minpos - 1, begin - 1, -1):
		arr[i].q += '1'

	if end - begin <= 2:
		return

	makebit(minpos, end)
	makebit(begin, minpos)

def mainout(first_s):
	print(Fore.YELLOW + f"\nLine length - {len(first_s)}") 
	print(Fore.YELLOW + f"Number of symbols - {len(arr)}")

	print(Fore.YELLOW + "Print \"P\"? Yes/No")
	inp = input()
	flag = True
	if inp == "No" or inp == "no" or inp == "2":
		flag = False

	if flag == True:
		print(Fore.GREEN + "A P Q")
		print(Style.RESET_ALL, end = '')
		sumbits = 0
		for i in range(len(arr)):
			sumbits += arr[i].p * len(arr[i].q)
			print(f"{arr[i].a} {arr[i].p} {arr[i].q}")
	else:
		print(Fore.GREEN + "A Q")
		print(Style.RESET_ALL, end = '')
		sumbits = 0
		for i in range(len(arr)):
			sumbits += arr[i].p * len(arr[i].q)
			print(f"{arr[i].a} {arr[i].q}")
	print("")

	print(Fore.YELLOW + f"Sum of bits - {sumbits}")
	print(Fore.YELLOW + f"Bit`s cost - {sumbits / len(first_s)}")

	for i in range(len(first_s)):
		print(Fore.RED + arr[used[ord(first_s[i])].second].q, end = '')
	print("")

	print(Fore.GREEN + "Complete!")
	print("")

def decrypt(scripted):
	pref = ""
	for i in range(len(scripted)):
		pref += scripted[i]
		for j in range(len(arr)):
			if pref == arr[j].q:
				print(Fore.RED + arr[j].a, end = '')
				pref = ""
				break
			
		
while(1):
	clear()
	print(Fore.YELLOW + "1) Encrypt 2) Decrypt 3) Clear cmd 4) Stop")
	print(Style.RESET_ALL, end = '')
	z = input()

	if z == "1":
		print(Fore.YELLOW + "Write a line")
		print(Style.RESET_ALL, end = '')
		first_s = input()

		input1(first_s)

		makefano(0, len(arr))

		mainout(first_s)

	elif z == "2":
		print(Fore.YELLOW + "Write the symbols with their codes\nWrite \"Stop\" when you end")
		while(1):
			print(Style.RESET_ALL, end = '')
			s = input()
			if s == "Stop" or s == "stop":
				break
			x: CODE = CODE('', 0, '')
			x.a = s[0]
			s = s[2:]
			x.q = s
			arr.append(x)

		print(Fore.YELLOW + "Write a binary line to decrypt")
		print(Style.RESET_ALL, end = '')
		first_s = input()

		decrypt(first_s)

		print("\n")
	elif z == "3":
		os.system("cls")
	else:
		print(Fore.RED + "Stopped")
		break
		
exit(0)