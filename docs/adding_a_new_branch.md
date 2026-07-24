# Creating and Pushing a Custom ArduPilot Branch to a Forked Repository

This guide explains how to create a new custom ArduPilot branch based on an existing ArduPilot branch or tag, then push the new branch into a personal fork repository (`ardupilot_sid`).

This workflow is useful for:

- Developing custom ArduPilot firmware modifications.
- Maintaining a custom branch based on an older ArduPilot release.
- Adding custom features while preserving ArduPilot history.
- Preparing firmware for SITL and real flight testing.

---

## 1. Clone the Official ArduPilot Repository

Clone the ArduPilot repository and initialize all submodules:

```bash
git clone --recurse-submodules https://github.com/ArduPilot/ardupilot.git
```

Navigate into the repository:

```bash
cd ardupilot
```

---

## 2. Fetch Available Branches and Tags

Update the local repository with all available branches and release tags:

```bash
git fetch --all --tags
```

View available branches:

```bash
git branch -a
```

View available tags:

```bash
git tag
```

---

## 3. Checkout the Desired ArduPilot Version

Checkout the desired ArduPilot branch or release tag that will serve as the base for the custom firmware.

Example using an ArduPilot release tag:

```bash
git checkout Plane-4.6.3
```

Example using the development branch:

```bash
git checkout master
```

Initialize and update all submodules:

```bash
git submodule update --init --recursive
```

Verify the current version:

```bash
git describe --tags
```

Example output:

```text
Plane-4.6.3
```

---

## 4. Configure Git Remotes

Check the current remote repository:

```bash
git remote -v
```

Example output:

```text
origin  https://github.com/ArduPilot/ardupilot.git (fetch)
origin  https://github.com/ArduPilot/ardupilot.git (push)
```

Rename the official ArduPilot repository remote:

```bash
git remote rename origin upstream
```

Verify the new remote name:

```bash
git remote -v
```

Expected output:

```text
upstream  https://github.com/ArduPilot/ardupilot.git (fetch)
upstream  https://github.com/ArduPilot/ardupilot.git (push)
```

---

## 5. Add the Custom Fork Repository

Add the personal fork as the new `origin` repository:

```bash
git remote add origin https://github.com/Xander-Mosley/ardupilot_sid.git
```

Verify the remote configuration:

```bash
git remote -v
```

Expected output:

```text
origin    https://github.com/Xander-Mosley/ardupilot_sid.git (fetch)
origin    https://github.com/Xander-Mosley/ardupilot_sid.git (push)

upstream  https://github.com/ArduPilot/ardupilot.git (fetch)
upstream  https://github.com/ArduPilot/ardupilot.git (push)
```

---

## 6. Create a New Custom Branch

Create a new branch based on the selected ArduPilot version:

```bash
git checkout -b <new branch name>
```

Example:

```bash
git checkout -b custom-plane-4.6.3
```

This creates a new branch containing the full history of the selected ArduPilot branch or tag.

---

## 7. Push the New Branch to the Fork

Stage the repository:

```bash
git add .
```

Commit the initial branch creation:

```bash
git commit -m "Adding a new branch from a different or an older ArduPilot branch/tag."
```

Push the new branch to the forked repository:

```bash
git push -u origin <new branch name>
```

Example:

```bash
git push -u origin custom-plane-4.6.3
```

The `-u` option sets the upstream tracking branch. Future pushes can then use:

```bash
git push
```

---

## 8. Modify the Custom ArduPilot Firmware

Make the desired firmware modifications.

Examples include:

- Adding custom AP_DDS topics.
- Adding custom MAVLink messages.
- Modifying flight control algorithms.
- Adding new parameters.
- Changing vehicle behavior.

Check modified files:

```bash
git status
```

---

## 9. Commit Firmware Changes

Stage modified files:

```bash
git add .
```

Commit the changes:

```bash
git commit -m "First customization to the different or older ArduPilot branch/tag in the new branch."
```

---

## 10. Push Firmware Updates

Push the committed changes:

```bash
git push
```

The custom ArduPilot firmware branch is now available in:

```text
https://github.com/Xander-Mosley/ardupilot_sid.git
```

---

## Complete Command Summary

```bash
# Clone ArduPilot
git clone --recurse-submodules https://github.com/ArduPilot/ardupilot.git
cd ardupilot

# Select ArduPilot version
git fetch --all --tags
git checkout <branch or tag>
git submodule update --init --recursive

# Configure remotes
git remote rename origin upstream
git remote add origin https://github.com/Xander-Mosley/ardupilot_sid.git

# Create custom branch
git checkout -b <new branch name>

# Push initial branch
git add .
git commit -m "Adding a new branch from a different or an older ArduPilot branch/tag."
git push -u origin <new branch name>

# Modify firmware
git status
git add .

# Commit modifications
git commit -m "First customization to the different or older ArduPilot branch/tag in the new branch."

# Push updates
git push
```
