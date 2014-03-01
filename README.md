Introduction
============

Team Communications
-------------------
Join us in #nyccamp on irc.freenode.net to chat about NYC Camp.

Pantheon + Github Workflow
-------------------------------------

Below we have a summary of the git workflow that the team is using for purposes of developing the NYC Camp site. This workflow should allow for a larger, more distributed team where people can contribute by biting off smaller portions of the work from the PM tool -- for 2014, this will be the Trello board/cards https://trello.com/nyccamp2014. We’re hoping to improve on the workflow from prior years, where people had to be rockstars and tackle almost the entire site (e.g., Mark/Father Shawn in 2011, and Tim in 2013).

Below we’ve added a ‘Brief Overview’ that outlines the 6 steps in our Git workflow. 

Our workflow varies slightly from the typical Pantheon workflow, in that we are using GitHub in order to make the workflow more transparent and allow for more detailed commenting/code review on GitHub (see steps 4 & 5). If you are new to Pantheon or want more details about the ‘under the hood process or Git commands, then you can see Section 3 of this document (which is a work in progress). 
 
Brief Overview (6 steps)
-------------------------------

### Step 1 - Local Dev Setup:
Setup your local dev environment. Ideally using the Vagrant-based approach set forth in Section 2 Below, or if preferable using the standard approach you’re comfortable with if you’re a more experienced developer.

### Step 2 - Pantheon Access:
Get Pantheon access  (i.e., added to project, and getting the connection settings)


### Step 3 - Pantheon Branch (Local & MultiDev):
Locally create a branch off ‘Integration’ on pantheon, and name it with your initial and a descriptive branch name: ‘yourinitials-feature-branch-name’; and then proceed using one of the two methods below depending on the scope of the work that you’re doing:
   1. Local Branch: For all smaller scopes of work, you can simply used your local branch to do your development and then create a PR for code review as outlined below
   2. Multidev: For broader scopes of work that are focused on major functionality or debugging, you case use the Pantheon UI to create a multidev environment on Pantheon which you and others can use to collaborate on test your work on Pantheon (note that you need to create the branch before you can spin up a multidev (see: https://www.youtube.com/watch?v=BI5azevzBZs).


### Step 4 - GitHub Pull Request(PR)/Code Review:
Once you’ve completed work on your new branch and are ready to contribute it back, a add Pull Request on GitHub in order to have another team member review your code
* Make PR against integration
* Tag others in your PR on Github for code review and/or email team@nyccamp.org


### Step 5 - Github Merge Pull Request:
* Have someone other than yourself review your PR/code, and once approved they should merge your PR into the integration branch on GitHub.
Step 5 - Push ‘integration’ from GitHub to Pantheon: 
* Once your PR has been reviewed and merged into integration on GitHub, it needs to be pushed from GitHub to ‘integration on Pantheon for final testing/review on the integration branch/MultiDev on Pantheon. One of the maintainers/gatekeepers of the Pantheon integration branch will complete this -- likely Tony, Eric, Robbie, Mai,  Forest or Willy (other can get more involved in helping with that if needed).

### Step 6 - Push ‘integration on Pantheon to Dev/Test/Live (Delete Branch)
Once things have been then in turn merge those changes into ‘master on pantheon and through to dev, test and live so that they appear on the site. Once that’s complete, the new branch (and any MultiDev) should then be deleted if it’s no longer need any more.

Branching Tips/Commands
--------------------------------

Fetch the upstream branches

    $ git fetch upstream

Make a new branch on your local that tracks the upstream branch. For example, if you are working on the ‘alpha’ feature, you would:

	$ git checkout -b alpha upstream/alpha

which checks you into the alpha branch, or

	$ git branch --track alpha upstream/alpha 

which makes the alpha branch but leaves you in your existing branch


Either way, do your work on the alpha feature in the alpha branch.

	$ git checkout alpha

Once you've finished the work on the alpha branch, commit your work to your local repository and push it to your origin.

	$ git push origin alpha

Github has recently added a green colored “Compare & pull request” button on your repository's web page, which makes things simpler.

Go to: `https://github.com/YOURUSERNAME/website`

You should see and your should click the “Compare & pull request”button

Notice on the next screen that the pull request is automatically set up between NYC-Camp:alpha ... YOURUSERNAME:alpha

Click the Send pull request button

If on the next screen, you see: `This pull request can be automatically merged.` and a “Merge pull request” button, **DO NOT** click that button. That would defeat the whole purpose of peer review. A gatekeeper will merge your pull request after it has been reviewed.

Assuming your work on the alpha branch is both code perfect and user experience perfect, you are done with the alpha branch and can, your time permitting, go on to a new feature and a new feature branch.

#### Read more in the [NYC Camp GitHub Wiki] (This is still a @TODO item)

[NYC Camp GitHub Wiki]:https://github.com/jmarkel/nyccamp2014/wiki


Set of tools to make COD7 more useful for conference planning.

In particular, the additions are aimed at making versions alpha2 and higher easier to use. COD 7alpha2 is the line that integrates OG, which brings with it both more powerful functionality, at the cost of some development pain. This module aims to bridge that gap.

Originally developed for NYC Camp website (http://nyccamp.org) with the intent of releasing back to COD community.

NB: Since NYC Camp is a 100% free event, initial Codify tools do not address paid registration issues. 

@TODO- Featurize session grid views. 

