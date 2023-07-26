#Install the Dependencies
pip install github3.py				

#GitHub Login
import github3
gh = github3.login(username="", token="")

#Lookup the Top 10 AI Repositories
top_ai_repos = gh.search_repositories(query='artifical intelligence', sort='stars')[:10]

#Merge the Repositories
import os
for repo in top_ai_repos:
	os.system("git clone {}".format(repo.clone_url))
	
#Fix Any Incompatible Codings
import os
for repo in top_ai_repos:
	os.system("git checkout --force")
	
#Create a New AI
# Create new file
with open('new_ai.py', 'w') as f:
	f.write('def new_ai():')
# Merge all repositories into the new file
	for repo in top_ai_repos:
		f.write(open(os.path.join(repo.name, 'main.py'), 'r').read())

#Create the Ability to Save Information
#Create a global array to save the info
info_list = []

#Modify the new_ai() to save any info
def new_ai():
	#YOUR CODE HERE
	info_list.append(info)
	
	#YOUR CODE HERE
