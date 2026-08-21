{-# LANGUAGE ForeignFunctionInterface #-}
module Main where

import Null0

-- required by GHC's module conventions, but never called: -no-hs-main
-- means the linker drops the usual RTS-wrapped main, and null0 only calls
-- the foreign-exported functions below
main :: IO ()
main = return ()

foreign export ccall "load" load :: IO ()

load :: IO ()
load = do
  clear blue
  drawCircle 100 100 50 red

-- callbacks (optional - implement, and foreign export, as needed)

-- foreign export ccall "update" update :: IO ()
-- update :: IO ()
-- update = return ()

-- foreign export ccall "unload" unload :: IO ()
-- unload :: IO ()
-- unload = return ()

-- foreign export ccall "buttonUp" buttonUp :: Int32 -> Word32 -> IO ()
-- buttonUp :: Int32 -> Word32 -> IO ()
-- buttonUp button player = return ()

-- foreign export ccall "buttonDown" buttonDown :: Int32 -> Word32 -> IO ()
-- buttonDown :: Int32 -> Word32 -> IO ()
-- buttonDown button player = return ()

-- foreign export ccall "keyUp" keyUp :: Int32 -> IO ()
-- keyUp :: Int32 -> IO ()
-- keyUp key = return ()

-- foreign export ccall "keyDown" keyDown :: Int32 -> IO ()
-- keyDown :: Int32 -> IO ()
-- keyDown key = return ()

-- foreign export ccall "mouseDown" mouseDown :: Int32 -> IO ()
-- mouseDown :: Int32 -> IO ()
-- mouseDown button = return ()

-- foreign export ccall "mouseUp" mouseUp :: Int32 -> IO ()
-- mouseUp :: Int32 -> IO ()
-- mouseUp button = return ()

-- foreign export ccall "mouseMoved" mouseMoved :: CFloat -> CFloat -> IO ()
-- mouseMoved :: CFloat -> CFloat -> IO ()
-- mouseMoved x y = return ()
