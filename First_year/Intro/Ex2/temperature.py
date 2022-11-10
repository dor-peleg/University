def is_it_summer_yet(min_temp, day1, day2, day3):
    """
    The function receives a minimum temperature and three-day temperature
    measurements and returns 'True' if in two of the three days the temperature
    was higher than the minimum temperature.
    """
    return (day1 > min_temp and day2 > min_temp) or (
                day1 > min_temp and day3 > min_temp) or (
                   day2 > min_temp and day3 > min_temp)
