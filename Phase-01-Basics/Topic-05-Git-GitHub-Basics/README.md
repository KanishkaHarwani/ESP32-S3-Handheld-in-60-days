# Topic 05: Git and GitHub Basics

**Week 1** · No firmware code. You will set up version control for the project you are about to build, from day one.

## Why this matters for embedded projects

Firmware bugs often come down to "what did I change since it last worked?" Git answers that. It also lets you try something risky (a new library, a driver rewrite) on a branch without risking your only working version.

## The commands you need

```bash
git init                     # start tracking a project (once)
git status                   # what changed since the last commit
git add <file>               # stage a file (or `git add .` for everything)
git commit -m "message"      # save a snapshot with a description
git log --oneline            # see history
```

Once you have a GitHub repo:

```bash
git remote add origin <repo-url>   # connect to GitHub (once)
git push                           # send commits to GitHub
git pull                           # bring down changes
```

## Branches, briefly

A branch is a parallel line of work:

```bash
git switch -c try-new-sensor   # create + switch to a new branch
# ...make changes, commit as normal...
git switch main                # back to main
git merge try-new-sensor       # bring the changes in once you are happy
```

A simple habit is enough here: one commit per topic or example on `main`. Save branches for real experiments.

## `.gitignore` for this repo

PlatformIO generates build artefacts you do not want in Git. **This repo is public**, so it must also keep secrets out:

```
.pio/
.vscode/
*.o
*.bin
include/secrets.h
```

Commit a `secrets.example.h` with placeholder values instead, so others know what to fill in:

```cpp
// secrets.example.h  (copy to secrets.h and fill in)
#define WIFI_SSID     "your-ssid"
#define WIFI_PASSWORD "your-password"
```

## If you already committed a secret

Deleting it in a later commit is not enough: it stays in history. Change the password or revoke the key first, then clean the history.

## Commit habit

Small, frequent commits with clear messages beat one giant commit:

```bash
git add .
git commit -m "Topic 06: GPIO blink example working"
```

## Check yourself

- What does `git status` show that `git log` does not?
- Why does `secrets.h` go in `.gitignore`?
- What should you do first if a password was pushed?

## What's next

Commit your Topic 04 blink example now. Then Week 2 starts with Topic 03 (architecture) and Topic 06 (GPIO).
