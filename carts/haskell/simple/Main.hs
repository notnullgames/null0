{-# LANGUAGE ForeignFunctionInterface #-}

module Main where

import Null0

-- wasm32-wasi-ghc builds a reactor module, so main is never the entry point
main :: IO ()
main = return ()

foreign export ccall "load" load :: IO ()

load :: IO ()
load = do
  clear blue
  drawCircle 100 100 50 red
  drawText fontDefault "hello from Haskell" 170 92 white

-- callbacks (optional - add a `foreign export ccall` for each one you want)
--
--   foreign export ccall "update" update :: IO ()
--   update :: IO ()
--   update = return ()
