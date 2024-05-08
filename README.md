
![](https://img.shields.io/github/languages/code-size/rpdjf/42-minishell?color=5BCFFF)

![](https://img.shields.io/badge/windows%20terminal-4D4D4D?style=for-the-badge&logo=windows%20terminal&logoColor=white)
![](https://img.shields.io/badge/WSL-0a97f5?style=for-the-badge&logo=linux&logoColor=white)

![](	https://img.shields.io/badge/mac%20os-000000?style=for-the-badge&logo=apple&logoColor=white)
# 🚀 42 Minishell 🚀
Ahoy, fellow code sailors! Welcome to my GitHub harbor, where the epic tales of the 42 Minishell project unfold. Dive into the coding seas, but remember, face the challenges alone before setting sail with my solutions, savvy?

![ezgif-1-65c8d3ee4c](https://github.com/RPDJF/42-minishell/assets/86334233/f80d9824-61e5-41d5-85d9-5a4503a295bc)


## What's Minishell, Anyway?
Minishell is a project that invites you to a symphony of shell scripting. It's like conducting an orchestra of commands—a true coding performance! 🎻🔍

## Cloning the Repository
Simply chant this command, and you're on board the ship:
```bash
git clone https://github.com/RPDJF/42-minishell.git
```

## Execute-it! 💻 

Just a few magic spells to summon your Minishell masterpiece:

- `make`: For a regular enchantment. Compile that code, and you're ready for the grand shell performance! This build isn't ready for use yet, please try SHITTY_TOKENIZER one.
- `make bonus`: Feeling adventurous? Add the bonus ingredients for an extra shell crescendo.
- `make clean`: Clear away the traces of your enchantment. A tidy workspace is a powerful workspace.
- `make fclean`: Need a clean slate? This erases all enchantments, leaving nothing behind.
- `make debug`: Unleash the debug sorcery using gdb. Warning: It leaves behind extra mystical artifacts not handled by `make fclean`.

Navigate this mystical realm with these commands, and may your Minishell journey be legendary! 🌟🔮

# Minishell: Crafting Our Own Bash

At the time of writing, minishell is my biggest coding project thus far. It's like creating our own mini-version of the bash shell, but don't let the "mini" part fool you! It took my friend and me more a little more than 1 month to design and implement our solution with bonuses and reach that 42-quality level with zero bugs in our code. 🤯

### What we learned 🧠

1. **Bash Syntax Mastery**: By diving into this project, we finally got a solid understanding of bash syntax in the command line. 📜
2. **Shell Implementation**: We explored how shells work and are implemented. It turns out there are four main phases to shell magic! 🌟
3. **Memory Management**: Handling a project bigger than our short-term memory could handle would have been a challenge. We had to write modular code and document it well so that even our future self could understand what we were thinking three weeks ago. 📝
4. **Collaboration**: Working together with someone on a code project was both rewarding and occasionally frustrating. It’s like solving creative puzzles together! 🤝


### Our Minishell Features 🛠️

1. **Bash 5.2 Base**: We boldly chose to base our minishell on bash 5.2, which differs significantly from the bash 3.2 installed on the Macs at école 42 Lausanne. 🆕
2. **Handling More Cases**: We wanted to cover more cases than necessary, including local variables. Because why settle for less, right? 💪
3. **Consistent Decisions**: To keep things coherent, we made some decisions. For example, when you run export without arguments, it displays all variables with “declare -x.” In reality, declare is a bash builtin, and the -x option declares a variable as an environment variable. Since we didn’t need the actual declare -x in our project, we replaced it with “export.” Makes sense, doesn’t it? 🤔
4. **Special Characters**: We even handled special characters like ~, which expands in minishell. We also handle special variables like `$?`, `$_` and `$SHELL` Because why not add a dash of magic? ✨
5. **Environment Handling**: Minishell gracefully handles cases when launched without an environment or when `PATH` is not defined, ensuring consistent behavior. 🌟

# Minishell: Our Approach

First things first, we all agreed that handling the bonus features would be ideal. So, we structured our entire project to accommodate bonus implementations right from the start. This way, even if we didn’t end up using them, we were prepared. And as it turned out, managing the bonuses wasn’t too challenging! 🌟

Then, we agreed to use https://github.com/RPDJF/betterft with some of my partner functions on this project. This library contains a garbage collector and allow us to ensure that no leaks are made possible. Still, we do not want our memory to grow up each time we malloc, so we still use `gfree()` function to free a memory and remove it from the garbage collector. This way, even if we forget to manually free some memory, our garbage will free it for us.

Our solution involved a clear separation between the parser and the executor. This allowed each of us to work independently on our respective parts without waiting for the other.

## Parsing Phases

1.  **Lexer**: In this phase, we retrieve the input and break it down into distinct words. Each word becomes a token that the parser can process. 📜
2.  **Parser**: The parser’s job is to tokenize all the words received from the lexer. It identifies commands, redirections, pipes, subshells, and more. If any issues arise, it returns the corresponding error. 🚦

### Tokens: What Are They?

A token is a well-defined instruction that the executor knows how to execute. It’s like a command waiting to happen! 💡

Here’s what our tokens looks like:

<p>
  <img src="https://github.com/RPDJF/42-minishell/assets/86334233/683321d4-f0cd-4770-943c-fbf816547d63" alt="tokens structure" width="600" height="auto"/>
</p>


The  `t_token_type`  serves as a simple enumerator to identify the type of token. Whether it’s a command, a pipe, or something else, the executor can deference the data to the corresponding structure based on the token type. 🧐

<p>
  <img src="https://github.com/RPDJF/42-minishell/assets/86334233/0b433ebc-ddde-48e3-9a65-b555362202bc" alt="tokens structure" width="600" height="auto"/>
</p>

## Executor Phase: Unleashing the Magic

In this phase, minishell transforms into a wizard, casting spells to execute commands. Here's how the magic unfolds:

1. **Here Documents First!**: Just like a wise sorcerer, minishell prioritizes executing here documents (those magical `<<` redirections). Why? Because they set the stage for everything else. No other commands should be executed before these mystical incantations. 🔮

2. **Piping**: Before execution, Minishell initializes the pipes tokens, updating Token contexts at the same time. It is important to do the piping before stdin and stdout since they have priority. 🛝

3. **Stdin and Stdout Shuffle**: Between each pipe context, `&&`, or `||`, minishell orchestrates a dance of stdin and stdout. Pipes connect commands like secret tunnels, allowing data to flow seamlessly. And when the curtain rises, stdout takes center stage, revealing the results. 🌊

4. **Command Execution**: The grand finale! Minishell steps onto the stage, ready to perform. If a command is recognized as a builtin (like `cd` or `export`), the corresponding builtin function takes the spotlight. If the builtin operates without pipes, it stays in the same process. But if pipes are involved, it gracefully forks into a new act. 🎭

5. **Command Forks**: Regular command executions are always forked. Each command's PID (Process ID) is stored in the command structure. Why? So that when the final curtain falls, minishell waits for all the forks, updates `$?`, and prepares for the next prompt. 🌟

6. **&& and || Drama**: When `&&` or `||` enters the scene, a dramatic `waitpid` takes center stage. It updates the command's status property, revealing whether the previous act succeeded or failed. 🎬

7. **Subshells (The Parentheses)**: Subshells are like hidden chambers within the castle. Minishell forks them, passing data into the executor function. These secret passages allow nested commands to unfold their mysteries. 🏰

8. **Var Init Cancelled**: If a command is already in progress, minishell cancels any var initialization. No need to double-cast spells! 🪄

And there you have it—the minishell saga! Feel free to explore our code in the repository. Feedback is always welcome! 🙌

Happy coding, fellow wizards! 🧙‍♂️🔍
