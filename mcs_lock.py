import threading

class MCSLock:
    class MCSNode:
        def __init__(self):
            self.next = None
            self.locked = False

    def __init__(self):
        self.thread_local = threading.local()
        self.thread_local.node = None
        self.queue = []

    def lock(self):
        node = self.thread_local.node = self.MCSNode()
        pred = self.queue[-1] if self.queue else None
        if pred:
            pred.next = node
        self.queue.append(node)
        if pred:
            while node.locked:
                pass

    def unlock(self):
        node = self.thread_local.node
        if node.next is None and self.queue[-1] == node:
            if not self.queue[-1].locked:
                if self.queue:
                    self.queue.pop()
            else:
                self.queue[-1].locked = False
                self.queue.pop()
        else:
            node.locked = False

def worker(lock, thread_id):
    lock.lock()
    print(f'Thread {thread_id} is in the critical section')
    lock.unlock()

if __name__ == "__main__":
    num_threads = 8
    lock = MCSLock()
    threads = []

    for i in range(num_threads):
        thread = threading.Thread(target=worker, args=(lock, i))
        threads.append(thread)

    for thread in threads:
        thread.start()

    for thread in threads:
        thread.join()
