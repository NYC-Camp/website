Introduction
============

Team Communications
-------------------
Join us in #nyccamp on [IRC](ircs://chat.freenode.net) to chat about NYC Camp.

Issues are tracked on GitHub at [http://github.com/NYC-Camp/website/issues](http://github.com/NYC-Camp/website/issues).

More info can be found on GitHub at [http://github.com/NYC-Camp/website/wiki](http://github.com/NYC-Camp/website/wiki).

Pantheon + Github Workflow
--------------------------
All code for the site comes from the GitHub Repository located at https://github.com/NYC-Camp/website. All work must be done from
Forks of that GitHub repository.  Do not clone the Pantheon repo, or commit and push to the Pantheon repo.

This code is continuously mirrored to Pantheon with http://hubdrop.io, managed by @jonpugh. Changes pushed to the GitHub
Repo will be pushed to Pantheon at most 4 minutes later.

Below we have a summary of the git workflow that the team is using for purposes of developing the NYC Camp site. This workflow should allow for a larger, more distributed team where people can contribute by biting off smaller portions of the work from the PM tool -- for 2014, this will be the Trello board/cards https://trello.com/nyccamp2014. We’re hoping to improve on the workflow from prior years, where people had to be rockstars and tackle almost the entire site (e.g., Mark/Father Shawn in 2011, and Tim in 2013).

Below we’ve added a ‘Brief Overview’ that outlines the 6 steps in our Git workflow.

Our workflow varies slightly from the typical Pantheon workflow, in that we are using GitHub in order to make the workflow more transparent and allow for more detailed commenting/code review on GitHub (see steps 4 & 5). If you are new to Pantheon or want more details about the ‘under the hood process or Git commands, then you can see Section 3 of this document (which is a work in progress).

Brief Overview (6 steps)
------------------------

### Step 1 - Local Dev Setup:
Setup your local dev environment. Ideally using the Vagrant-based approach set forth in our [wiki].
[wiki]: https://github.com/NYC-Camp/website/wiki/Vagrant-setup

### Step 2 - Pantheon Access:
Get Pantheon access  (i.e., added to project, and getting the connection settings)

This is optional, now that the code is being mirrored from GitHub. You only need Pantheon access if you need to access
their dashboard.

### Step 3 - Fork the Repo:

Visit https://github.com/NYC-Camp/website and click "Fork" to create your own copy of the source code.

If your change is minor you may work in the `master` branch of your fork.  If your change is major, you should make a new
branch within your fork.

### Step 4 - GitHub Pull Request(PR)/Code Review:

Once you’ve completed work on your fork and are ready to contribute it back, a add Pull Request on GitHub in order to
have another team member review your code.

To create a pull request, visit your fork's page and click "Pull Request" at the top right of the files table.

Tag others in your PR on Github for code review and/or email team@nyccamp.org

### Step 5 - Github Merge Pull Request:

Have someone other than yourself review your PR/code, and once approved, they will merge your PR into the main NYC-Camp/website repo.

Once merged, the branch may be deleted

### Step 6 - Deploy to Test, then Live

After the merge the code will make it's way to the Pantheon dev site automatically. A QA team member will review all of
the new changes on Dev, and once approved, will deploy the changes to Test to ensure it works with the latest Live database.

Once test is reviewed and all is well, the QA team member will deploy those commits to live.

Pull Requests & Peer Review
---------------------------

Github has recently added a green colored “Compare & pull request” button on your repository's web page, which makes things simpler.

Go to: `https://github.com/YOURUSERNAME/website`

You should see and your should click the “Compare & pull request”button

Notice on the next screen that the pull request is automatically set up between NYC-Camp:master ... YOURUSERNAME:master

Click the Send pull request button

If on the next screen, you see: `This pull request can be automatically merged.` and a “Merge pull request” button, **DO NOT** click that button. That would defeat the whole purpose of peer review. A gatekeeper will merge your pull request after it has been reviewed.

Assuming your work on your fork is both code perfect and user experience perfect, you are done with the fork and can, your time permitting, go on to a new feature and a new feature branch.
