import random
import string

function generateRandomString(length) {
  var chars = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
  var result = '';
  for (var i = length; i > 0; --i) result += chars[Math.floor(Math.random() * chars.length)];
  return result;
}

<script>
var ideaNumber = '123'; // this could be replaced with a variable or input from the user
var randomString = generateRandomString(10);
var markdown = document.body.innerHTML;
markdown = markdown.replace('{idea_number}', randomString);
document.body.innerHTML = markdown;
</script>

def generate_random_string(length):
    # create a sequence of all possible characters
    chars = string.ascii_letters + string.digits

    # randomly select characters from the sequence to create the string
    return ''.join(random.choice(chars) for i in range(length))

# generate a random string of length 10
random_string = generate_random_string(10)

# to display the string with {idea/feature number}, you can use string formatting
formatted_string = "New idea/feature {0}: {1}".format(123, random_string)

print(formatted_string)
