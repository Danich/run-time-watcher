# RUN-TIME-WATCHER
Small zsh script which displays time spent on every command execution

## Like this:
```
./run-time-watcher % ls
README.md  src	zfunc
  >> 50 ms (own: 0.019ms)                                                                                                                                                                                          
./run-time-watcher % sleep 1
  >> 1 s, 23 ms (own: 0.019ms)    
```

## Installation:
1. Put `zfunc` contents in your zsh `fpath`
2. Put executable somewhere within `$PATH`
3. Restart zsh