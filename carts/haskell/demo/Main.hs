{-# LANGUAGE ForeignFunctionInterface #-}
module Main where

import Data.Int (Int32)
import Data.IORef
import System.IO.Unsafe (unsafePerformIO)
import Null0

-- required by GHC's module conventions, but never called: -no-hs-main
-- means the linker drops the usual RTS-wrapped main, and null0 only calls
-- the foreign-exported functions below
main :: IO ()
main = return ()

-- Haskell has no mutable globals, so a persistent frame counter needs an
-- IORef created once at module scope.
{-# NOINLINE frameCounter #-}
frameCounter :: IORef Int32
frameCounter = unsafePerformIO (newIORef 0)

foreign export ccall "update" update :: IO ()
update :: IO ()
update = do
  clear darkgray
  drawText fontDefault "null0 demo" 20 20 white
  drawRectangle 40 80 100 70 red
  drawCircle 220 115 45 green
  drawTriangle 320 150 400 150 360 60 blue
  drawLine 40 250 600 250 lightgray
  drawPolygon
    [ Vector 460 80
    , Vector 520 80
    , Vector 550 140
    , Vector 520 200
    , Vector 460 200
    , Vector 430 140
    ]
    purple

  frame <- readIORef frameCounter
  writeIORef frameCounter (frame + 1)
  let x = frame `mod` 600
  drawCircle (x + 20) 350 20 yellow

  drawText fontDefault "shapes + animation + text" 20 440 orange

-- callbacks (optional - implement, and foreign export, as needed)

-- foreign export ccall "load" load :: IO ()
-- load :: IO ()
-- load = return ()

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
