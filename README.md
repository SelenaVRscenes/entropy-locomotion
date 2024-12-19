# Yuliya Unreal Project 


## Repository information

This .git repository aim to store Yuliya's developement in Unreal Engine 5 as part of her Phd work.

## Repository Structure :

The project structure is organised as follow :

_Git bases componnents :_
-  `.gitignore` : A custom _.gitignore_ for Unreal 5 based project forked from [ue5-gitignore](https://github.com/MOZGIII/ue5-gitignore) and adapted to our needs

-  `.gitattributes` : Not all the files from git repository are being processed in the same way within different software or machines (ex: the case of the *EOL* characters). This .gitattributes file normalise this process by specifing rules of operations for files/folders based on their filetypes or path (here for **git-lfs** purposes). More on this [here](https://rehansaeed.com/gitattributes-best-practices/) and [here](https://dev.to/deadlybyte/please-add-gitattributes-to-your-git-repository-1jld).


_Unreal components :_ 
Unreal projects are structured as follow :

- `/Source` : C++ source code is stored here. As this directory is managed by standard git (and not git-lfs) only text file are allowed here (**so no binary here : `.dlls`, `.exes`, `.zips` ...**). If you have Unreal generated text files (ex: specific to the developer machines) those should be ignored by git with additional entries in .gitignore.


- `/Config` : Engine and game config files.


- `/Plugins` : Every plugin lives in a subdirectory of the '/Plugins' dir. It is expected that each plugin will have it's own .gitignore file in it's subdirectory, as well other required specific git tweaks.


- `/Content` : Game assets in Unreal Engine formats, '.uasset' and '.umap'. Only those two file types are allowed, everything else is ignored.


- `/RawContent` : **This directory is managed entirely by *git-lfs*.**
`/RawContent` is a directory where you store assets in their source formats, in contrast to /Content, where assets are stored in the engine format (after the import). Having an asset in a source format is useful when you're still making updates to it. It may be a good idea to also have separate repos for managing work-in-progress assets (maybe in smaller collections or even idividually).

## How to use

1. Set up `git` and `git-lfs`.
2. Copy `.gitignore` and `.gitattributes` to your project.

## Caveats

Take special care when working with plugins. Plugin structure is not very well defined, so you will be able to mess the git repo up with big files if you commit them to a plugin directory.

## Contributing

### Rules

This repo uses UNIX-style line endings and UTF-8.
Make sure every line in a text file is ended with a newline (especially the last line in a file, git should notify you if you've lost it). This is due to how lines are [defined](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap03.html#tag_03_206). Feel free to search the web for more info on why to end every file with an "empty line".

### How to contribute

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request




## Getting started

To make it easy for you to get started with GitLab, here's a list of recommended next steps.

Already a pro? Just edit this README.md and make it your own. Want to make it easy? [Use the template at the bottom](#editing-this-readme)!

## Add your files

- [ ] [Create](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#create-a-file) or [upload](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#upload-a-file) files
- [ ] [Add files using the command line](https://docs.gitlab.com/ee/gitlab-basics/add-file.html#add-a-file-using-the-command-line) or push an existing Git repository with the following command:

```
cd existing_repo
git remote add origin https://gitlab.inria.fr/sandbox/yuliya-unreal-project.git
git branch -M main
git push -uf origin main
```

## Integrate with your tools

- [ ] [Set up project integrations](https://gitlab.inria.fr/sandbox/yuliya-unreal-project/-/settings/integrations)

## Collaborate with your team

- [ ] [Invite team members and collaborators](https://docs.gitlab.com/ee/user/project/members/)
- [ ] [Create a new merge request](https://docs.gitlab.com/ee/user/project/merge_requests/creating_merge_requests.html)
- [ ] [Automatically close issues from merge requests](https://docs.gitlab.com/ee/user/project/issues/managing_issues.html#closing-issues-automatically)
- [ ] [Enable merge request approvals](https://docs.gitlab.com/ee/user/project/merge_requests/approvals/)
- [ ] [Automatically merge when pipeline succeeds](https://docs.gitlab.com/ee/user/project/merge_requests/merge_when_pipeline_succeeds.html)

## Test and Deploy

Use the built-in continuous integration in GitLab.

- [ ] [Get started with GitLab CI/CD](https://docs.gitlab.com/ee/ci/quick_start/index.html)
- [ ] [Analyze your code for known vulnerabilities with Static Application Security Testing(SAST)](https://docs.gitlab.com/ee/user/application_security/sast/)
- [ ] [Deploy to Kubernetes, Amazon EC2, or Amazon ECS using Auto Deploy](https://docs.gitlab.com/ee/topics/autodevops/requirements.html)
- [ ] [Use pull-based deployments for improved Kubernetes management](https://docs.gitlab.com/ee/user/clusters/agent/)
- [ ] [Set up protected environments](https://docs.gitlab.com/ee/ci/environments/protected_environments.html)

***

# Editing this README

When you're ready to make this README your own, just edit this file and use the handy template below (or feel free to structure it however you want - this is just a starting point!). Thank you to [makeareadme.com](https://www.makeareadme.com/) for this template.

## Suggestions for a good README
Every project is different, so consider which of these sections apply to yours. The sections used in the template are suggestions for most open source projects. Also keep in mind that while a README can be too long and detailed, too long is better than too short. If you think your README is too long, consider utilizing another form of documentation rather than cutting out information.

## Name
Choose a self-explaining name for your project.

## Description
Let people know what your project can do specifically. Provide context and add a link to any reference visitors might be unfamiliar with. A list of Features or a Background subsection can also be added here. If there are alternatives to your project, this is a good place to list differentiating factors.

## Badges
On some READMEs, you may see small images that convey metadata, such as whether or not all the tests are passing for the project. You can use Shields to add some to your README. Many services also have instructions for adding a badge.

## Visuals
Depending on what you are making, it can be a good idea to include screenshots or even a video (you'll frequently see GIFs rather than actual videos). Tools like ttygif can help, but check out Asciinema for a more sophisticated method.

## Installation
Within a particular ecosystem, there may be a common way of installing things, such as using Yarn, NuGet, or Homebrew. However, consider the possibility that whoever is reading your README is a novice and would like more guidance. Listing specific steps helps remove ambiguity and gets people to using your project as quickly as possible. If it only runs in a specific context like a particular programming language version or operating system or has dependencies that have to be installed manually, also add a Requirements subsection.

## Usage
Use examples liberally, and show the expected output if you can. It's helpful to have inline the smallest example of usage that you can demonstrate, while providing links to more sophisticated examples if they are too long to reasonably include in the README.

## Support
Tell people where they can go to for help. It can be any combination of an issue tracker, a chat room, an email address, etc.

## Roadmap
If you have ideas for releases in the future, it is a good idea to list them in the README.

## Contributing
State if you are open to contributions and what your requirements are for accepting them.

For people who want to make changes to your project, it's helpful to have some documentation on how to get started. Perhaps there is a script that they should run or some environment variables that they need to set. Make these steps explicit. These instructions could also be useful to your future self.

You can also document commands to lint the code or run tests. These steps help to ensure high code quality and reduce the likelihood that the changes inadvertently break something. Having instructions for running tests is especially helpful if it requires external setup, such as starting a Selenium server for testing in a browser.

## Authors and acknowledgment
Show your appreciation to those who have contributed to the project.

## License
For open source projects, say how it is licensed.

## Project status
If you have run out of energy or time for your project, put a note at the top of the README saying that development has slowed down or stopped completely. Someone may choose to fork your project or volunteer to step in as a maintainer or owner, allowing your project to keep going. You can also make an explicit request for maintainers.
