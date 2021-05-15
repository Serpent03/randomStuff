# need to implement ord(char) into this lol

from random import randint, choice

encryptionLookupValues = dict(
    charList = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'],
    numList = ['1', '2', '3', '4', '5', '6', '7', '8', '9', '0'],
    operatorList = ["'", " ", '"', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '+', '[', ']', ':', ';', '{', '}', '/', '?', '<', '>', ',', '.', '`', '~', '|'],
    charDecrypt = ['XdhR', 'SUbf', 'WHdb', 'DbRvE', 'WOFfc', 'DOHFF', 'cRFnc', 'XIHfv', 'xcUF'],
    operDecrypt = ['iAFg', 'WD8v', 'asucE', 'xBRcR', 'iCivw', 'CNUWd', 'IWbfbc', 'CFCcWD', 'cIWFB'],
    numDecrypt = ['XBRc', 'jTudD', 'URVF', 'cByrF', 'DIOfd', 'CFbnnf', 'xOFnF', 'pCHC', 'fqhog'],
)

def encryptWord(word):

    encryptedWord = ''
    
    for chars in word:
        if chars.lower() in encryptionLookupValues['charList']:     #pass upper and lower chars accordingly
            encryptKey = choice(encryptionLookupValues['charDecrypt'])
            if chars.islower():
                rand = randint(1, 1024)
                indexVal = encryptionLookupValues['charList'].index(chars)
                encryptedWord += f'_{encryptKey}_{rand + indexVal}_{rand+2}_1{rand}'
            elif chars.isupper():
                rand = randint(1, 1024)
                indexVal = encryptionLookupValues['charList'].index(chars.lower())
                encryptedWord += f'_{encryptKey}_{rand + indexVal}_{rand+5}_2{rand}'

        elif chars in encryptionLookupValues['numList']:    # number encryption
            rand = randint(1, 1024)
            indexVal = encryptionLookupValues['numList'].index(chars)
            encryptKey = choice(encryptionLookupValues['numDecrypt'])
            encryptedWord += f'_{encryptKey}_{rand + indexVal}_{rand+10}'

        elif chars in encryptionLookupValues['operatorList']:
            rand = randint(1, 1024)
            indexVal = encryptionLookupValues['operatorList'].index(chars)
            encryptKey = choice(encryptionLookupValues['operDecrypt'])
            encryptedWord += f'_{encryptKey}_{rand + indexVal}_{rand*2}'
        
    print(f"\nEncrypted: {encryptedWord}\n")
    return decryptWord(encryptedWord)

def decryptWord(encryptedQuery):

    decryptedWord = ''
    modulator = encryptedQuery.split('_')

    for i in modulator:       # set up passed modulator
        if i == '':
            modulator.remove(i)

    #return modulator

    for char in range(len(modulator)):
        if modulator[char] in encryptionLookupValues['charDecrypt']:  # check if passed letter is upper() or lower()
            if modulator[char+3] == f"1{(int(modulator[char+2])-2)}":
                decryptedWord += encryptionLookupValues['charList'][int(modulator[char+1]) - (int(modulator[char+2])-2)]
            if modulator[char+3] == f"2{(int(modulator[char+2])-5)}":
                decryptedWord += encryptionLookupValues['charList'][int(modulator[char+1]) - (int(modulator[char+2])-5)].upper()
        
        if modulator[char] in encryptionLookupValues['numDecrypt']:
            decryptedWord += encryptionLookupValues['numList'][int(modulator[char+1]) - (int(modulator[char+2])-10)]
        
        if modulator[char] in encryptionLookupValues['operDecrypt']:
            decryptedWord += encryptionLookupValues['operatorList'][int(modulator[char+1]) - (int(modulator[char+2])//2)]
    
    return f"Decrypted: {decryptedWord}"

if __name__ == "__main__":
    print(encryptWord(str(input("Input: "))))