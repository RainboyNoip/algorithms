## 说明

使用[lazyVim](https://www.lazyvim.org/) 作为编辑器.

因为我需要一个写代码的工具,这里选lazyvim


## 下载

根据这个视频[](https://www.youtube.com/watch?v=LkHjJlSgKZY)

和根据[nvim文档](https://neovim.io/doc/user/starting.html#%24NVIM_APPNAME)

> This variable controls the sub-directory that Nvim will read from (and auto-create) in each of the base directories.
> For example, setting `$NVIM_APPNAME` to "foo" before starting will cause Nvim to look for configuration files in `$XDG_CONFIG_HOME/foo` instead of `$XDG_CONFIG_HOME/nvim`.

```
alias lv="$NVIM_APPNAME=lazyvim nvim"
```


## 配置

本目录下的核心配置`rainboy-algo.lua`,放到`lazyvim/start`下载的的`lua/plugin/rainboy-algo`下面
这个就是我的配置

q:如何地位sqnr

## 自动补全的配置


不支持reg匹配,所以不好用,我还是使用原来的`ultisnips`

如果需要在`nvim-cmp`下使用`ultisnips`,那就需要[cmp-nvim-ultisnips](https://github.com/quangnguyen30192/cmp-nvim-ultisnips),
它是`UltiSnips completion source for nvim-cmp`




## clangd lsp 的配置

- c++ lsp, 加上`-I path/to/algorithms/include` 这个路径

先查看[lazy.nvim](https://github.com/folke/lazy.nvim)的文档

第一查看[`nvim-lspconfig`](https://github.com/neovim/nvim-lspconfig)文档

根据

- [nvim-lspconfig clang配置](https://github.com/neovim/nvim-lspconfig/blob/master/doc/server_configurations.md#clangd)
- `compile_flags.txt` https://stackoverflow.com/a/68462390

```
{
  "neovim/nvim-lspconfig",
  opts = {
      servers = {
          clangd = {
              cmd = {"clangd", "--compile-commands-dir","path/to/layznvim"}
            }
        }
    }
}
```

并在这个目录下加入`compile_flags.txt`
