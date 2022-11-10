class Countdown:
    """
    class that controls the countdown clock.
    """
    def __init__(self, root):
        self._root = root
        self._timer = False
        self._milliseconds_left = 180000

    def get_timer(self):
        """
        return the current state of timer
        :return: True if there is time left, False otherwise.
        """
        return self._timer

    def countdown(self):
        """
        checks if there is time left. if yes, Reduces the remaining time and
        use after method to check again.
        when time is up change the timer to False
        :return: None
        """
        if self._milliseconds_left > 0:
            self._timer = True
            self._milliseconds_left -= 13
            self._root.after(13, self.countdown)
        else:
            self._timer = False

    def get_time_left(self):
        """
        change the format of the remaining tome to 00:00:000
        :return: the remaining time.
        """
        minutes, seconds = divmod(self._milliseconds_left, 60000)
        seconds, milliseconds = divmod(seconds, 1000)
        return '{:02}:{:02}:{:03}'.format(int(minutes), int(seconds),
                                          int(milliseconds))
