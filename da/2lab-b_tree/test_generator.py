# -*- coding: utf-8 -*-
import sys
import random
import string
import copy
from random import choice
from string import ascii_lowercase
def get_random_key():
    return ''.join(choice(ascii_lowercase) for i in range(4))

if __name__ == "__main__":
    count_of_tests = 1
    actions = ["?", "+", "-"]
    acts_file = ["Load test", "Save test"]
    for enum in range( count_of_tests ):
        keys = {}
        save_file = {}
        test_file_name = "tests/{:02d}".format( enum + 1 )
        with open( "{0}.t".format( test_file_name ), 'w' ) as output_file, \
             open( "{0}.a".format( test_file_name ), "w" ) as answer_file:

            # Для каждого файла генерируем от 1 до 100 тестов.
            for _ in range( 100000 ):
                action = random.choice( actions )
                if action == "+":
                    key = get_random_key()
                    value = random.randint( 1, 2**64-1 )
                    output_file.write("+ {0} {1}\n".format( key, value ))
                    key = key.lower()
                    # Если в нашем словаре уже есть такой ключ, то ответе должно быть 
                    # сказано, что он существует, иначе --- успешное добавление.
                    answer = "Exist"
                    if key not in keys:
                        answer = "OK"
                        keys[key] = value
                    answer_file.write( "{0}\n".format( answer ) )

                elif action == "?":
                    search_exist_element = random.choice( [ True, False ] )
                    key = random.choice( [ key for key in keys.keys() ] ) if search_exist_element and len( keys.keys() ) > 0 else get_random_key()
                    output_file.write( "{0}\n".format( key ) )
                    key = key.lower()
                    if key in keys:
                        answer = "OK: {0}".format( keys[key] )
                    else:
                        answer = "NoSuchWord"
                    answer_file.write( "{0}\n".format( answer ) ) 
                    
                elif action == "-":
                    key = get_random_key()
                    output_file.write("- {0}\n".format(key))
                    key = key.lower()
                    answer = "NoSuchWord"
                    if key in keys:
                        del keys[key]
                        answer = "OK"
                    answer_file.write("{0}\n".format( answer ) )
                
                elif action == "!":
                    act_file = random.choice(acts_file)
                    if act_file == "Save test":
                        output_file.write("{0} {1}\n".format( action, act_file ))
                        save_file = keys.copy()
                        #for key in keys:
                        #    save_file[key] = keys[key];
                        #    print(keys)
                        answer = "OK"
                    elif act_file == "Load test":
                        output_file.write("{0} {1}\n".format( action, act_file ))
                        keys = {}
                        keys = save_file.copy()
                        #for key in save_file:
                        #    keys[key] = save_file[key];
                        #print(keys)
                        answer = "OK"
                    answer_file.write( "{0}\n".format( answer ) )
                        
