# Array of tests to run (in order)
# Each test contains
#   description - 
#   steps - A list of steps to perform, each step can have
#       inputs - A list of tuples for the inputs to apply at that step
#       *time - The time (in ms) to wait before continuing to the next step 
#           and before checking expected values for this step. The time should be a multiple of
#           the period of the system
#       *iterations - The number of clock ticks to wait (periods)
#       expected - The expected value at the end of this step (after the "time" has elapsed.) 
#           If this value is incorrect the test will fail early before completing.
#       * only one of these should be used
#   expected - The expected output (as a list of tuples) at the end of this test
# An example set of tests is shown below. It is important to note that these tests are not "unit tests" in 
# that they are not ran in isolation but in the order shown and the state of the device is not reset or 
# altered in between executions (unless preconditions are used).
tests = [ 
#    {'description': 'PINA: 0x00 => PORTB: 0x00',
#    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 5 } ],
#    'expected': [('PORTB',0x00)],
#    },
#    {'description': 'PINA: 0x01 => PORTB: 0x01',
#    'steps': [ {'inputs': [('PINA',0x01)], 'iterations': 5 } ],
#    'expected': [('PORTB',0x01)],
#    },
#    {'description': 'PINA: 0x02 => PORTB: 0x00',
#    'steps': [ {'inputs': [('PINA',0x02)], 'iterations': 5 } ],
#    'expected': [('PORTB',0x00)],
#    },
#    {'description': 'PINA: 0x03 => PORTB: 0x00',
#    'steps': [ {'inputs': [('PINA',0x03)], 'iterations': 5 } ],
#    'expected': [('PORTB',0x00)],
#    },
#     {'description': 'PINA: 0x00 => PORTC: 0x04',
#     'steps': [ {'inputs': [('PINA',0x00)],
#      'iterations': 5 } ],
#      'expected': [('PORTC',0x04)],
#     },
#     {'description': 'PINA: 0x01 => PORTC: 0x03',
#      'steps': [ {'inputs': [('PINA',0x01)],
#      'iterations': 5 } ],
#      'expected': [('PORTC',0x03)],
#     },
#     {'description': 'PINA: 0x02 => PORTC: 0x03',
#      'steps': [ {'inputs': [('PINA',0x02)],
#      'iterations': 5 } ],
#      'expected': [('PORTC',0x03)],
#     },
#     {'description': 'PINA: 0x03 => PORTC: 0x02',
#      'steps': [ {'inputs': [('PINA',0x03)],
#      'iterations': 5 } ],
#      'expected': [('PORTC',0x02)],
#     },
#     {'description': 'PINA: 0x04 => PORTC: 0x03',
#      'steps': [ {'inputs': [('PINA',0x04)],
#      'iterations': 5 } ],
#      'expected': [('PORTC',0x03)],
#     },
#     {'description': 'PINA: 0x05 => PORTC: 0x02',
#      'steps': [ {'inputs': [('PINA',0x05)],
#      'iterations': 5 } ],
#      'expected': [('PORTC',0x02)],
#     },
#     {'description': 'PINA: 0x02 => PORTC: 0x02',
#      'steps': [ {'inputs': [('PINA',0x06)],
#      'iterations': 5 } ],
#      'expected': [('PORTC',0x02)],
#     },
#     {'description': 'PINA: 0x07 => PORTC: 0x01',
#      'steps': [ {'inputs': [('PINA',0x07)],
#      'iterations': 5 } ],
#      'expected': [('PORTC',0x01)],
#     },
#     {'description': 'PINA: 0x08 => PORTC: 0x03',
#      'steps': [ {'inputs': [('PINA',0x08)],
#      'iterations': 5 } ],
#      'expected': [('PORTC',0x03)],
#     },
#     {'description': 'PINA: 0x09 => PORTC: 0x02',
#      'steps': [ {'inputs': [('PINA',0x09)],
#      'iterations': 5 } ],
#      'expected': [('PORTC',0x02)],
#     },
#     {'description': 'PINA: 0x0A => PORTC: 0x02',
#      'steps': [ {'inputs': [('PINA',0x0A)],
#      'iterations': 5 } ],
#      'expected': [('PORTC',0x02)],
#     },
#     {'description': 'PINA: 0x0B => PORTC: 0x01',
#      'steps': [ {'inputs': [('PINA',0x0B)],
#      'iterations': 5 } ],
#      'expected': [('PORTC',0x01)],
#     },
#     {'description': 'PINA: 0x02 => PORTC: 0x02',
#      'steps': [ {'inputs': [('PINA',0x0C)],
#      'iterations': 5 } ],
#      'expected': [('PORTC',0x02)],
#     },
#     {'description': 'PINA: 0x0D => PORTC: 0x01',
#      'steps': [ {'inputs': [('PINA',0x0D)],
#      'iterations': 5 } ],
#      'expected': [('PORTC',0x01)],
#     },
#     {'description': 'PINA: 0x0E => PORTC: 0x01',
#      'steps': [ {'inputs': [('PINA',0x0E)],
#      'iterations': 5 } ],
#      'expected': [('PORTC',0x01)],
#     },
#     {'description': 'PINA: 0x0F => PORTC: 0x80',
#      'steps': [ {'inputs': [('PINA',0x0F)],
#      'iterations': 5 } ],
#      'expected': [('PORTC',0x80)],
#     },
#
     #testing weight
     {'description': 'PINA:50 (0x32), PINB:40 (0x28), PINC:50 (0x32)',
      'steps': [ {'inputs': [('PINA',0x32),('PINB',0x28),('PINC',0x32)],
      'iterations': 5 }],
      'expected': [('PORTD', 0x8C)],
     }
     #testing limit
     {'description': 'PINA:60 (0x3C), PINB:40 (0x28), PINC:50 (0x32)',
      'steps': [ {'inputs': [('PINA',0x3C),('PINB',0x28),('PINC',0x32)],
      'iterations': 5 }],
      'expected': [('PORTD', 0x97)],
     }
     #testing balance
     {'description': 'PINA:10 (0x0A), PINB:40 (0x28), PINC:90 (0x5A)',
      'steps': [ {'inputs': [('PINA',0x0A),('PINB',0x28),('PINC',0x5A)],
      'iterations': 5 }],
      'expected': [('PORTD', 0x8E)],
     }
    ]

watch = ['PORTC']

# Optionally you can add a set of "watch" variables these need to be global or static and may need
# to be scoped at the function level (for static variables) if there are naming conflicts. The 
# variables listed here will display everytime you hit (and stop at) a breakpoint
#watch = ['<function>::<static-var>','PORTB']

