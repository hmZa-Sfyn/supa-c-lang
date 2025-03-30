import os,datetime,time

while True:
	print("....")

	os.system(f"git add . && git commit -m \"batman{datetime.datetime.now()}\" && git push origin main ")

	time.sleep(4)

	print(datetime.datetime.now())
