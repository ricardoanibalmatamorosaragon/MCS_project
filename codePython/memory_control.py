from memory_profiler import memory_usage
from datetime import datetime

def measure_memory_usage(target_call, target_args, log_filename=None, memory_denominator=1024.0**2, memory_usage_refresh=0.005):
    """
    measure the memory usage of a function call in python.\n
    Note: one may have to restart python to get accurate results.\n
    :param target_call: function to be tested\n
    :param target_args: arguments of the function in a tuple\n
    :param memory_usage_refresh: how frequent the memory is measured, default to 0.005 seconds\n
    :return: max memory usage in kB (on Linux/Ubuntu 14.04), may depend on OS
    """
    import time
    import threading
    import psutil
    import os

    class StoppableThread(threading.Thread):
        def __init__(self, target, args):
            super(StoppableThread, self).__init__(target=target, args=args)
            self.daemon = True
            self.__monitor = threading.Event()
            self.__monitor.set()
            self.__has_shutdown = False

        def run(self):
            '''Overloads the threading.Thread.run'''
            # Call the User's Startup functions
            self.startup()

            # use the run method from Superclass threading.Thread
            super(StoppableThread, self).run()

            # Clean up
            self.cleanup()

            # Flag to the outside world that the thread has exited
            # AND that the cleanup is complete
            self.__has_shutdown = True

        def stop(self):
            self.__monitor.clear()

        def isRunning(self):
            return self.__monitor.isSet()

        def isShutdown(self):
            return self.__has_shutdown

        def mainloop(self):
            '''
            Expected to be overwritten in a subclass!!
            Note that Stoppable while(1) is handled in the built in "run".
            '''
            pass

        def startup(self):
            '''Expected to be overwritten in a subclass!!'''
            pass

        def cleanup(self):
            '''Expected to be overwritten in a subclass!!'''
            pass

    class MyLibrarySniffingClass(StoppableThread):
        def __init__(self, target, args):
            super(MyLibrarySniffingClass, self).__init__(target=target, args=args)
            self.target_function = target
            self.results = None

        def startup(self):
            # Overload the startup function
            pass


        def cleanup(self):
            # Overload the cleanup function
            pass

        process = psutil.Process(os.getpid())

    process = psutil.Process(os.getpid())
    my_thread = MyLibrarySniffingClass(target_call, target_args)
    start_mem = process.memory_info().rss
    my_thread.start()
    delta_mem = 0
    max_memory = 0

    while(True):
        time.sleep(memory_usage_refresh)
        current_mem = process.memory_info().rss
        delta_mem = current_mem - start_mem
        if delta_mem > max_memory:
            max_memory = delta_mem
            # print "Max memory usage is %f" % max_memory
        # Check to see if the library call is complete
        if my_thread.isShutdown():
            pass
            break

    current_mem = process.memory_info().rss
    delta_mem = current_mem - start_mem
    if delta_mem > max_memory:
        max_memory = delta_mem

    max_memory /= memory_denominator

    if log_filename is not None:
        with open(log_filename, "a") as f:
            tmp_str = str(max_memory) + ","
            f.write(tmp_str)

    #print "MAX Memory Usage in MB: %f" % max_memory
    return max_memory
