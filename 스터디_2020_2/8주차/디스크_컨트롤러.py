#Import heapq module.
import heapq

def solution(jobs):
    count, last, answer = 0, -1, 0
    #Use list as heapq.
    heap = []
    #Sort job with request time.
    jobs.sort()
    #First request time.
    time = jobs[0][0]
    while count < len(jobs):
        for s, t in jobs:
            #If job's request time in last request time + wait time to last request time + wait time + running time  
            if last < s <= time:
                #Push tuple (request time, running time) 
                heapq.heappush(heap, (t, s))
        if len(heap) > 0:
            count += 1
            last = time
            #Term = running time, start = request time
            term, start = heapq.heappop(heap)
            time += term
            answer += (time - start)
        else:
            #Wait Time
            time += 1
    return answer//len(jobs)
