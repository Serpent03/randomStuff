# need to implement ord(char) into this lol

import sieveOfEratothenes

# generate new keys every time
sieveOfEratothenes.writeKeys()


def encryptWord(word):

    encryptedWord = ''

    for char in word:
        encryptionKey = round(sieveOfEratothenes.readKeys(), 0)
        encryptionWord = f"{ord(char) * encryptionKey}_{encryptionKey}f_"
        encryptedWord += encryptionWord

    print(f"\nEncrypted object: {encryptedWord}\n")
    return decryptWord(encryptedWord)
    

def decryptWord(encryptedQuery):

    decryptedWord = ''
    modulator = encryptedQuery.split('_')

    for i in modulator:
        if i == '':
            modulator.remove(i)

    for key in range(len(modulator)):
        try:
            if modulator[key+1][-1] == 'f':     # modulator[key] == encrypted message. modulator[key+1] == passkey
                decryptedWord += chr(int(modulator[key])//int(modulator[key+1][:-1]))
        except:
            pass

    return f"Decrypted object: {decryptedWord}"

if __name__ == "__main__":
    print(encryptWord(str(input("Input: "))))