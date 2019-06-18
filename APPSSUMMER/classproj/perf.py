import time
from threading import Thread
from requests.auth import HTTPBasicAuth
from random import randint
import json, sys
import requests

success = 0
failed = 0

class RequestGenerator(Thread):
    def __init__(self, val):
        ''' Constructor. '''
        Thread.__init__(self)
        self.val = val

    def detail_college(self, college_id):
        url = "http://localhost:8080/api/v1/colleges/" + str(college_id)
        response = requests.get(url, auth=HTTPBasicAuth('hvharsha998', 'abcdEFGH123$%^'))
        if response.status_code != 200:
            # print("request failed in detail college " + str(college_id), response.status_code)
            raise Exception

        return json.loads(response.text)


    def list_colleges(self):
        url = "http://localhost:8080/api/v1/colleges"
        response = requests.get(url, auth=HTTPBasicAuth('hvharsha998', 'abcdEFGH123$%^'))
        if response.status_code != 200:
            # print("request failed in list college ", response.status_code)
            raise Exception

        return json.loads(response.text)

    def run(self):
        global success
        global failed
        try:
            start = time.time()
            colleges = self.list_colleges()
            if len(colleges) > 0:
                college_id = randint(28, 44)
                college_detail = self.detail_college(college_id)
                # print(college_detail)
            end = time.time()
            print("Request took ", (end - start), "ms to complete for ", self.val, " iteration")
            success = success + 1
        except Exception as e:
            # print("Caught exception ", e, " in handling of request ", self.val)
            failed = failed + 1


def main():
    request_generators = []
    try:
        thread_count = int(sys.argv[1])
    except Exception as e:
        print(e)
        print('First arg (thread count) missing!')
        return

    for i in range(0, thread_count):
        request_generator = RequestGenerator(i)
        request_generators.append(request_generator)
        request_generator.setName("Request Generator " + str(i))
        request_generator.start()

    for i in range(0, thread_count):
        request_generators[i].join()

    print('Completed activity')
    print('Total threads ', thread_count, ' success ', success, ' failed ', failed)


# Run following code when the program starts
if __name__ == '__main__':
    main()