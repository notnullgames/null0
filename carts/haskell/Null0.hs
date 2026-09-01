-- null0 - Haskell bindings for the null0 fantasy console
--
-- GENERATED FILE - do not edit by hand. See tools/gen_cart_haskell.js
--
-- Usage:
--
-- > import Null0
-- >
-- > update :: IO ()
-- > update = clear blue

{-# LANGUAGE ForeignFunctionInterface #-}
module Null0 where

import Foreign
import Foreign.C.String
import Foreign.C.Types
import Data.Int
import Data.Word

-- | Sfx parameters.
data SfxParams = SfxParams
  { sfxparams_randSeed :: Word32
  , sfxparams_waveType :: Int32
  , sfxparams_attackTime :: CFloat
  , sfxparams_sustainTime :: CFloat
  , sfxparams_sustainPunch :: CFloat
  , sfxparams_decayTime :: CFloat
  , sfxparams_startFrequency :: CFloat
  , sfxparams_minFrequency :: CFloat
  , sfxparams_slide :: CFloat
  , sfxparams_deltaSlide :: CFloat
  , sfxparams_vibratoDepth :: CFloat
  , sfxparams_vibratoSpeed :: CFloat
  , sfxparams_changeAmount :: CFloat
  , sfxparams_changeSpeed :: CFloat
  , sfxparams_squareDuty :: CFloat
  , sfxparams_dutySweep :: CFloat
  , sfxparams_repeatSpeed :: CFloat
  , sfxparams_phaserOffset :: CFloat
  , sfxparams_phaserSweep :: CFloat
  , sfxparams_lpfCutoff :: CFloat
  , sfxparams_lpfCutoffSweep :: CFloat
  , sfxparams_lpfResonance :: CFloat
  , sfxparams_hpfCutoff :: CFloat
  , sfxparams_hpfCutoffSweep :: CFloat
  } deriving (Show, Eq)

instance Storable SfxParams where
  sizeOf _ = 96
  alignment _ = 4
  peek p = SfxParams <$> (peekByteOff p 0 :: IO Word32) <*> (peekByteOff p 4 :: IO Int32) <*> (peekByteOff p 8 :: IO CFloat) <*> (peekByteOff p 12 :: IO CFloat) <*> (peekByteOff p 16 :: IO CFloat) <*> (peekByteOff p 20 :: IO CFloat) <*> (peekByteOff p 24 :: IO CFloat) <*> (peekByteOff p 28 :: IO CFloat) <*> (peekByteOff p 32 :: IO CFloat) <*> (peekByteOff p 36 :: IO CFloat) <*> (peekByteOff p 40 :: IO CFloat) <*> (peekByteOff p 44 :: IO CFloat) <*> (peekByteOff p 48 :: IO CFloat) <*> (peekByteOff p 52 :: IO CFloat) <*> (peekByteOff p 56 :: IO CFloat) <*> (peekByteOff p 60 :: IO CFloat) <*> (peekByteOff p 64 :: IO CFloat) <*> (peekByteOff p 68 :: IO CFloat) <*> (peekByteOff p 72 :: IO CFloat) <*> (peekByteOff p 76 :: IO CFloat) <*> (peekByteOff p 80 :: IO CFloat) <*> (peekByteOff p 84 :: IO CFloat) <*> (peekByteOff p 88 :: IO CFloat) <*> (peekByteOff p 92 :: IO CFloat)
  poke p (SfxParams f_randSeed f_waveType f_attackTime f_sustainTime f_sustainPunch f_decayTime f_startFrequency f_minFrequency f_slide f_deltaSlide f_vibratoDepth f_vibratoSpeed f_changeAmount f_changeSpeed f_squareDuty f_dutySweep f_repeatSpeed f_phaserOffset f_phaserSweep f_lpfCutoff f_lpfCutoffSweep f_lpfResonance f_hpfCutoff f_hpfCutoffSweep) = pokeByteOff p 0 f_randSeed >> pokeByteOff p 4 f_waveType >> pokeByteOff p 8 f_attackTime >> pokeByteOff p 12 f_sustainTime >> pokeByteOff p 16 f_sustainPunch >> pokeByteOff p 20 f_decayTime >> pokeByteOff p 24 f_startFrequency >> pokeByteOff p 28 f_minFrequency >> pokeByteOff p 32 f_slide >> pokeByteOff p 36 f_deltaSlide >> pokeByteOff p 40 f_vibratoDepth >> pokeByteOff p 44 f_vibratoSpeed >> pokeByteOff p 48 f_changeAmount >> pokeByteOff p 52 f_changeSpeed >> pokeByteOff p 56 f_squareDuty >> pokeByteOff p 60 f_dutySweep >> pokeByteOff p 64 f_repeatSpeed >> pokeByteOff p 68 f_phaserOffset >> pokeByteOff p 72 f_phaserSweep >> pokeByteOff p 76 f_lpfCutoff >> pokeByteOff p 80 f_lpfCutoffSweep >> pokeByteOff p 84 f_lpfResonance >> pokeByteOff p 88 f_hpfCutoff >> pokeByteOff p 92 f_hpfCutoffSweep

-- | The 2D size of something (width/height.)
data Dimensions = Dimensions
  { dimensions_width :: Int32
  , dimensions_height :: Int32
  } deriving (Show, Eq)

instance Storable Dimensions where
  sizeOf _ = 8
  alignment _ = 4
  peek p = Dimensions <$> (peekByteOff p 0 :: IO Int32) <*> (peekByteOff p 4 :: IO Int32)
  poke p (Dimensions f_width f_height) = pokeByteOff p 0 f_width >> pokeByteOff p 4 f_height

-- | The 2D position of something (x/y.)
data Vector = Vector
  { vector_x :: Int32
  , vector_y :: Int32
  } deriving (Show, Eq)

instance Storable Vector where
  sizeOf _ = 8
  alignment _ = 4
  peek p = Vector <$> (peekByteOff p 0 :: IO Int32) <*> (peekByteOff p 4 :: IO Int32)
  poke p (Vector f_x f_y) = pokeByteOff p 0 f_x >> pokeByteOff p 4 f_y

-- | The 2D position + size of something (x/y/w/h.)
data Rectangle = Rectangle
  { rectangle_x :: Int32
  , rectangle_y :: Int32
  , rectangle_width :: Int32
  , rectangle_height :: Int32
  } deriving (Show, Eq)

instance Storable Rectangle where
  sizeOf _ = 16
  alignment _ = 4
  peek p = Rectangle <$> (peekByteOff p 0 :: IO Int32) <*> (peekByteOff p 4 :: IO Int32) <*> (peekByteOff p 8 :: IO Int32) <*> (peekByteOff p 12 :: IO Int32)
  poke p (Rectangle f_x f_y f_width f_height) = pokeByteOff p 0 f_x >> pokeByteOff p 4 f_y >> pokeByteOff p 8 f_width >> pokeByteOff p 12 f_height

-- | An RGBA color.
data Color = Color
  { color_r :: Word8
  , color_g :: Word8
  , color_b :: Word8
  , color_a :: Word8
  } deriving (Show, Eq)

instance Storable Color where
  sizeOf _ = 4
  alignment _ = 4
  peek p = Color <$> (peekByteOff p 0 :: IO Word8) <*> (peekByteOff p 1 :: IO Word8) <*> (peekByteOff p 2 :: IO Word8) <*> (peekByteOff p 3 :: IO Word8)
  poke p (Color f_r f_g f_b f_a) = pokeByteOff p 0 f_r >> pokeByteOff p 1 f_g >> pokeByteOff p 2 f_b >> pokeByteOff p 3 f_a

-- | A custom property on a tilemap, layer, object, or tile. Only the member named by `type` is meaningful - a PROP_BOOL is 0/1 in `integer`, and a PROP_COLOR is RGBA bytes in `integer`.
data TilemapProp = TilemapProp
  { tilemapprop_name :: CString
  , tilemapprop_type :: Int32
  , tilemapprop_integer :: Int32
  , tilemapprop_number :: CFloat
  , tilemapprop_text :: CString
  } deriving (Show, Eq)

instance Storable TilemapProp where
  sizeOf _ = 20
  alignment _ = 4
  peek p = TilemapProp <$> (peekByteOff p 0 :: IO CString) <*> (peekByteOff p 4 :: IO Int32) <*> (peekByteOff p 8 :: IO Int32) <*> (peekByteOff p 12 :: IO CFloat) <*> (peekByteOff p 16 :: IO CString)
  poke p (TilemapProp f_name f_type f_integer f_number f_text) = pokeByteOff p 0 f_name >> pokeByteOff p 4 f_type >> pokeByteOff p 8 f_integer >> pokeByteOff p 12 f_number >> pokeByteOff p 16 f_text

-- | An object from an object-layer of a tilemap. This is the map's initial state - carts own whatever they spawn from it.
data TilemapObject = TilemapObject
  { tilemapobject_id :: Int32
  , tilemapobject_name :: CString
  , tilemapobject_type :: CString
  , tilemapobject_gid :: Int32
  , tilemapobject_x :: CFloat
  , tilemapobject_y :: CFloat
  , tilemapobject_width :: CFloat
  , tilemapobject_height :: CFloat
  , tilemapobject_rotation :: CFloat
  , tilemapobject_visible :: Int32
  } deriving (Show, Eq)

instance Storable TilemapObject where
  sizeOf _ = 40
  alignment _ = 4
  peek p = TilemapObject <$> (peekByteOff p 0 :: IO Int32) <*> (peekByteOff p 4 :: IO CString) <*> (peekByteOff p 8 :: IO CString) <*> (peekByteOff p 12 :: IO Int32) <*> (peekByteOff p 16 :: IO CFloat) <*> (peekByteOff p 20 :: IO CFloat) <*> (peekByteOff p 24 :: IO CFloat) <*> (peekByteOff p 28 :: IO CFloat) <*> (peekByteOff p 32 :: IO CFloat) <*> (peekByteOff p 36 :: IO Int32)
  poke p (TilemapObject f_id f_name f_type f_gid f_x f_y f_width f_height f_rotation f_visible) = pokeByteOff p 0 f_id >> pokeByteOff p 4 f_name >> pokeByteOff p 8 f_type >> pokeByteOff p 12 f_gid >> pokeByteOff p 16 f_x >> pokeByteOff p 20 f_y >> pokeByteOff p 24 f_width >> pokeByteOff p 28 f_height >> pokeByteOff p 32 f_rotation >> pokeByteOff p 36 f_visible

-- | The screen is image 0
screen :: Word32
screen = 0

screenWidth :: Int32
screenWidth = 640

screenHeight :: Int32
screenHeight = 480

-- | The built-in font
fontDefault :: Word32
fontDefault = 0

lightgray :: Color
lightgray = Color 200 200 200 255

gray :: Color
gray = Color 130 130 130 255

darkgray :: Color
darkgray = Color 80 80 80 255

yellow :: Color
yellow = Color 253 249 0 255

gold :: Color
gold = Color 255 203 0 255

orange :: Color
orange = Color 255 161 0 255

pink :: Color
pink = Color 255 109 194 255

red :: Color
red = Color 230 41 55 255

maroon :: Color
maroon = Color 190 33 55 255

green :: Color
green = Color 0 228 48 255

lime :: Color
lime = Color 0 158 47 255

darkgreen :: Color
darkgreen = Color 0 117 44 255

skyblue :: Color
skyblue = Color 102 191 255 255

blue :: Color
blue = Color 0 121 241 255

darkblue :: Color
darkblue = Color 0 82 172 255

purple :: Color
purple = Color 200 122 255 255

violet :: Color
violet = Color 135 60 190 255

darkpurple :: Color
darkpurple = Color 112 31 126 255

beige :: Color
beige = Color 211 176 131 255

brown :: Color
brown = Color 127 106 79 255

darkbrown :: Color
darkbrown = Color 76 63 47 255

white :: Color
white = Color 255 255 255 255

black :: Color
black = Color 0 0 0 255

blank :: Color
blank = Color 0 0 0 0

magenta :: Color
magenta = Color 255 0 255 255

raywhite :: Color
raywhite = Color 245 245 245 255

-- | The current tagged version of null0 engine
null0Version :: String
null0Version = "0.0.21"

-- Potential image-filtering techniques for scale/etc.
filterNearestneighbor :: Int32
filterNearestneighbor = 0

filterBilinear :: Int32
filterBilinear = 1

filterSmooth :: Int32
filterSmooth = 2

-- Represents a Sfx preset type.
sfxCoin :: Int32
sfxCoin = 0

sfxLaser :: Int32
sfxLaser = 1

sfxExplosion :: Int32
sfxExplosion = 2

sfxPowerup :: Int32
sfxPowerup = 3

sfxHurt :: Int32
sfxHurt = 4

sfxJump :: Int32
sfxJump = 5

sfxSelect :: Int32
sfxSelect = 6

sfxSynth :: Int32
sfxSynth = 7

-- Represents a keyboard key.
keyInvalid :: Int32
keyInvalid = 0

keySpace :: Int32
keySpace = 32

keyApostrophe :: Int32
keyApostrophe = 39

keyComma :: Int32
keyComma = 44

keyMinus :: Int32
keyMinus = 45

keyPeriod :: Int32
keyPeriod = 46

keySlash :: Int32
keySlash = 47

key0 :: Int32
key0 = 48

key1 :: Int32
key1 = 49

key2 :: Int32
key2 = 50

key3 :: Int32
key3 = 51

key4 :: Int32
key4 = 52

key5 :: Int32
key5 = 53

key6 :: Int32
key6 = 54

key7 :: Int32
key7 = 55

key8 :: Int32
key8 = 56

key9 :: Int32
key9 = 57

keySemicolon :: Int32
keySemicolon = 59

keyEqual :: Int32
keyEqual = 61

keyA :: Int32
keyA = 65

keyB :: Int32
keyB = 66

keyC :: Int32
keyC = 67

keyD :: Int32
keyD = 68

keyE :: Int32
keyE = 69

keyF :: Int32
keyF = 70

keyG :: Int32
keyG = 71

keyH :: Int32
keyH = 72

keyI :: Int32
keyI = 73

keyJ :: Int32
keyJ = 74

keyK :: Int32
keyK = 75

keyL :: Int32
keyL = 76

keyM :: Int32
keyM = 77

keyN :: Int32
keyN = 78

keyO :: Int32
keyO = 79

keyP :: Int32
keyP = 80

keyQ :: Int32
keyQ = 81

keyR :: Int32
keyR = 82

keyS :: Int32
keyS = 83

keyT :: Int32
keyT = 84

keyU :: Int32
keyU = 85

keyV :: Int32
keyV = 86

keyW :: Int32
keyW = 87

keyX :: Int32
keyX = 88

keyY :: Int32
keyY = 89

keyZ :: Int32
keyZ = 90

keyLeftBracket :: Int32
keyLeftBracket = 91

keyBackslash :: Int32
keyBackslash = 92

keyRightBracket :: Int32
keyRightBracket = 93

keyGraveAccent :: Int32
keyGraveAccent = 96

keyWorld1 :: Int32
keyWorld1 = 161

keyWorld2 :: Int32
keyWorld2 = 162

keyEscape :: Int32
keyEscape = 256

keyEnter :: Int32
keyEnter = 257

keyTab :: Int32
keyTab = 258

keyBackspace :: Int32
keyBackspace = 259

keyInsert :: Int32
keyInsert = 260

keyDelete :: Int32
keyDelete = 261

keyRight :: Int32
keyRight = 262

keyLeft :: Int32
keyLeft = 263

keyDown' :: Int32
keyDown' = 264

keyUp' :: Int32
keyUp' = 265

keyPageUp :: Int32
keyPageUp = 266

keyPageDown :: Int32
keyPageDown = 267

keyHome :: Int32
keyHome = 268

keyEnd :: Int32
keyEnd = 269

keyCapsLock :: Int32
keyCapsLock = 280

keyScrollLock :: Int32
keyScrollLock = 281

keyNumLock :: Int32
keyNumLock = 282

keyPrintScreen :: Int32
keyPrintScreen = 283

keyPause :: Int32
keyPause = 284

keyF1 :: Int32
keyF1 = 290

keyF2 :: Int32
keyF2 = 291

keyF3 :: Int32
keyF3 = 292

keyF4 :: Int32
keyF4 = 293

keyF5 :: Int32
keyF5 = 294

keyF6 :: Int32
keyF6 = 295

keyF7 :: Int32
keyF7 = 296

keyF8 :: Int32
keyF8 = 297

keyF9 :: Int32
keyF9 = 298

keyF10 :: Int32
keyF10 = 299

keyF11 :: Int32
keyF11 = 300

keyF12 :: Int32
keyF12 = 301

keyF13 :: Int32
keyF13 = 302

keyF14 :: Int32
keyF14 = 303

keyF15 :: Int32
keyF15 = 304

keyF16 :: Int32
keyF16 = 305

keyF17 :: Int32
keyF17 = 306

keyF18 :: Int32
keyF18 = 307

keyF19 :: Int32
keyF19 = 308

keyF20 :: Int32
keyF20 = 309

keyF21 :: Int32
keyF21 = 310

keyF22 :: Int32
keyF22 = 311

keyF23 :: Int32
keyF23 = 312

keyF24 :: Int32
keyF24 = 313

keyF25 :: Int32
keyF25 = 314

keyKp0 :: Int32
keyKp0 = 320

keyKp1 :: Int32
keyKp1 = 321

keyKp2 :: Int32
keyKp2 = 322

keyKp3 :: Int32
keyKp3 = 323

keyKp4 :: Int32
keyKp4 = 324

keyKp5 :: Int32
keyKp5 = 325

keyKp6 :: Int32
keyKp6 = 326

keyKp7 :: Int32
keyKp7 = 327

keyKp8 :: Int32
keyKp8 = 328

keyKp9 :: Int32
keyKp9 = 329

keyKpDecimal :: Int32
keyKpDecimal = 330

keyKpDivide :: Int32
keyKpDivide = 331

keyKpMultiply :: Int32
keyKpMultiply = 332

keyKpSubtract :: Int32
keyKpSubtract = 333

keyKpAdd :: Int32
keyKpAdd = 334

keyKpEnter :: Int32
keyKpEnter = 335

keyKpEqual :: Int32
keyKpEqual = 336

keyLeftShift :: Int32
keyLeftShift = 340

keyLeftControl :: Int32
keyLeftControl = 341

keyLeftAlt :: Int32
keyLeftAlt = 342

keyLeftSuper :: Int32
keyLeftSuper = 343

keyRightShift :: Int32
keyRightShift = 344

keyRightControl :: Int32
keyRightControl = 345

keyRightAlt :: Int32
keyRightAlt = 346

keyRightSuper :: Int32
keyRightSuper = 347

keyMenu :: Int32
keyMenu = 348

-- Represents a gamepad button.
gamepadButtonUnknown :: Int32
gamepadButtonUnknown = 0

gamepadButtonUp :: Int32
gamepadButtonUp = 1

gamepadButtonRight :: Int32
gamepadButtonRight = 2

gamepadButtonDown' :: Int32
gamepadButtonDown' = 3

gamepadButtonLeft :: Int32
gamepadButtonLeft = 4

gamepadButtonY :: Int32
gamepadButtonY = 5

gamepadButtonB :: Int32
gamepadButtonB = 6

gamepadButtonA :: Int32
gamepadButtonA = 7

gamepadButtonX :: Int32
gamepadButtonX = 8

gamepadButtonLeftShoulder :: Int32
gamepadButtonLeftShoulder = 9

gamepadButtonLeftTrigger :: Int32
gamepadButtonLeftTrigger = 10

gamepadButtonRightShoulder :: Int32
gamepadButtonRightShoulder = 11

gamepadButtonRightTrigger :: Int32
gamepadButtonRightTrigger = 12

gamepadButtonSelect :: Int32
gamepadButtonSelect = 13

gamepadButtonMenu :: Int32
gamepadButtonMenu = 14

gamepadButtonStart :: Int32
gamepadButtonStart = 15

gamepadButtonLeftThumb :: Int32
gamepadButtonLeftThumb = 16

gamepadButtonRightThumb :: Int32
gamepadButtonRightThumb = 17

-- Represents a mouse button.
mouseButtonUnknown :: Int32
mouseButtonUnknown = 0

mouseButtonLeft :: Int32
mouseButtonLeft = 1

mouseButtonRight :: Int32
mouseButtonRight = 2

mouseButtonMiddle :: Int32
mouseButtonMiddle = 3

-- The kind of a layer in a tilemap.
layerNone :: Int32
layerNone = 0

layerTile :: Int32
layerTile = 1

layerObject :: Int32
layerObject = 2

layerImage :: Int32
layerImage = 3

layerGroup :: Int32
layerGroup = 4

-- The type of a tilemap property's value. Tiled's "file" properties arrive as PROP_STRING.
propNone :: Int32
propNone = 0

propInt :: Int32
propInt = 1

propBool :: Int32
propBool = 2

propFloat :: Int32
propFloat = 3

propString :: Int32
propString = 4

propColor :: Int32
propColor = 5

-- COLORS

foreign import ccall unsafe "color_tint" c_colorTint :: Ptr Color -> Ptr Color -> IO (Ptr Color)
-- | Tint a color with another color.
colorTint :: Color -> Color -> IO Color
colorTint color tint =
  with color $ \color_p ->
  with tint $ \tint_p ->
    c_colorTint color_p tint_p >>= peek

foreign import ccall unsafe "color_fade" c_colorFade :: Ptr Color -> CFloat -> IO (Ptr Color)
-- | Fade a color.
colorFade :: Color -> CFloat -> IO Color
colorFade color alpha =
  with color $ \color_p ->
    c_colorFade color_p alpha >>= peek

foreign import ccall unsafe "color_brightness" c_colorBrightness :: Ptr Color -> CFloat -> IO (Ptr Color)
-- | Change the brightness of a color.
colorBrightness :: Color -> CFloat -> IO Color
colorBrightness color factor =
  with color $ \color_p ->
    c_colorBrightness color_p factor >>= peek

foreign import ccall unsafe "color_invert" c_colorInvert :: Ptr Color -> IO (Ptr Color)
-- | Invert a color.
colorInvert :: Color -> IO Color
colorInvert color =
  with color $ \color_p ->
    c_colorInvert color_p >>= peek

foreign import ccall unsafe "color_alpha_blend" c_colorAlphaBlend :: Ptr Color -> Ptr Color -> IO (Ptr Color)
-- | Blend 2 colors together.
colorAlphaBlend :: Color -> Color -> IO Color
colorAlphaBlend dst src =
  with dst $ \dst_p ->
  with src $ \src_p ->
    c_colorAlphaBlend dst_p src_p >>= peek

foreign import ccall unsafe "color_contrast" c_colorContrast :: Ptr Color -> CFloat -> IO (Ptr Color)
-- | Change contrast of a color.
colorContrast :: Color -> CFloat -> IO Color
colorContrast color contrast =
  with color $ \color_p ->
    c_colorContrast color_p contrast >>= peek

foreign import ccall unsafe "color_bilinear_interpolate" c_colorBilinearInterpolate :: Ptr Color -> Ptr Color -> Ptr Color -> Ptr Color -> CFloat -> CFloat -> IO (Ptr Color)
-- | Interpolate colors.
colorBilinearInterpolate :: Color -> Color -> Color -> Color -> CFloat -> CFloat -> IO Color
colorBilinearInterpolate color00 color01 color10 color11 coordinateX coordinateY =
  with color00 $ \color00_p ->
  with color01 $ \color01_p ->
  with color10 $ \color10_p ->
  with color11 $ \color11_p ->
    c_colorBilinearInterpolate color00_p color01_p color10_p color11_p coordinateX coordinateY >>= peek

-- GRAPHICS

foreign import ccall unsafe "new_image" c_newImage :: Int32 -> Int32 -> Ptr Color -> IO Word32
-- | Create a new blank image.
newImage :: Int32 -> Int32 -> Color -> IO Word32
newImage width height color =
  with color $ \color_p ->
    c_newImage width height color_p

foreign import ccall unsafe "image_copy" c_imageCopy :: Word32 -> IO Word32
-- | Copy an image to a new image.
imageCopy :: Word32 -> IO Word32
imageCopy image = c_imageCopy image

foreign import ccall unsafe "image_subimage" c_imageSubimage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> IO Word32
-- | Create an image from a region of another image.
imageSubimage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> IO Word32
imageSubimage image x y width height = c_imageSubimage image x y width height

foreign import ccall unsafe "clear" c_clear :: Ptr Color -> IO ()
-- | Clear the screen.
clear :: Color -> IO ()
clear color =
  with color $ \color_p ->
    c_clear color_p

foreign import ccall unsafe "draw_point" c_drawPoint :: Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a single pixel on the screen.
drawPoint :: Int32 -> Int32 -> Color -> IO ()
drawPoint x y color =
  with color $ \color_p ->
    c_drawPoint x y color_p

foreign import ccall unsafe "draw_line" c_drawLine :: Int32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a line on the screen.
drawLine :: Int32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
drawLine startPosX startPosY endPosX endPosY color =
  with color $ \color_p ->
    c_drawLine startPosX startPosY endPosX endPosY color_p

foreign import ccall unsafe "draw_rectangle" c_drawRectangle :: Int32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a filled rectangle on the screen.
drawRectangle :: Int32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
drawRectangle posX posY width height color =
  with color $ \color_p ->
    c_drawRectangle posX posY width height color_p

foreign import ccall unsafe "draw_triangle" c_drawTriangle :: Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a filled triangle on the screen.
drawTriangle :: Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
drawTriangle x1 y1 x2 y2 x3 y3 color =
  with color $ \color_p ->
    c_drawTriangle x1 y1 x2 y2 x3 y3 color_p

foreign import ccall unsafe "draw_ellipse" c_drawEllipse :: Int32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a filled ellipse on the screen.
drawEllipse :: Int32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
drawEllipse centerX centerY radiusX radiusY color =
  with color $ \color_p ->
    c_drawEllipse centerX centerY radiusX radiusY color_p

foreign import ccall unsafe "draw_circle" c_drawCircle :: Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a filled circle on the screen.
drawCircle :: Int32 -> Int32 -> Int32 -> Color -> IO ()
drawCircle centerX centerY radius color =
  with color $ \color_p ->
    c_drawCircle centerX centerY radius color_p

foreign import ccall unsafe "draw_polygon" c_drawPolygon :: Ptr Vector -> Word32 -> Ptr Color -> IO ()
-- | Draw a filled polygon on the screen.
drawPolygon :: [Vector] -> Color -> IO ()
drawPolygon points color =
  withArrayLen points $ \points_count points_ptr ->
  with color $ \color_p ->
    c_drawPolygon points_ptr (fromIntegral points_count) color_p

foreign import ccall unsafe "draw_arc" c_drawArc :: Int32 -> Int32 -> CFloat -> CFloat -> CFloat -> Int32 -> Ptr Color -> IO ()
-- | Draw a filled arc on the screen.
drawArc :: Int32 -> Int32 -> CFloat -> CFloat -> CFloat -> Int32 -> Color -> IO ()
drawArc centerX centerY radius startAngle endAngle segments color =
  with color $ \color_p ->
    c_drawArc centerX centerY radius startAngle endAngle segments color_p

foreign import ccall unsafe "draw_rectangle_rounded" c_drawRectangleRounded :: Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a filled round-rectangle on the screen.
drawRectangleRounded :: Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
drawRectangleRounded x y width height cornerRadius color =
  with color $ \color_p ->
    c_drawRectangleRounded x y width height cornerRadius color_p

foreign import ccall unsafe "draw_image" c_drawImage :: Word32 -> Int32 -> Int32 -> IO ()
-- | Draw an image on the screen.
drawImage :: Word32 -> Int32 -> Int32 -> IO ()
drawImage src posX posY = c_drawImage src posX posY

foreign import ccall unsafe "draw_image_tint" c_drawImageTint :: Word32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a tinted image on the screen.
drawImageTint :: Word32 -> Int32 -> Int32 -> Color -> IO ()
drawImageTint src posX posY tint =
  with tint $ \tint_p ->
    c_drawImageTint src posX posY tint_p

foreign import ccall unsafe "draw_image_rotated" c_drawImageRotated :: Word32 -> Int32 -> Int32 -> CFloat -> CFloat -> CFloat -> Int32 -> IO ()
-- | Draw an image, rotated, on the screen.
drawImageRotated :: Word32 -> Int32 -> Int32 -> CFloat -> CFloat -> CFloat -> Int32 -> IO ()
drawImageRotated src posX posY degrees offsetX offsetY filter = c_drawImageRotated src posX posY degrees offsetX offsetY filter

foreign import ccall unsafe "draw_image_flipped" c_drawImageFlipped :: Word32 -> Int32 -> Int32 -> CBool -> CBool -> CBool -> IO ()
-- | Draw an image, flipped, on the screen.
drawImageFlipped :: Word32 -> Int32 -> Int32 -> Bool -> Bool -> Bool -> IO ()
drawImageFlipped src posX posY flipHorizontal flipVertical flipDiagonal = c_drawImageFlipped src posX posY (fromBool flipHorizontal) (fromBool flipVertical) (fromBool flipDiagonal)

foreign import ccall unsafe "draw_image_scaled" c_drawImageScaled :: Word32 -> Int32 -> Int32 -> CFloat -> CFloat -> CFloat -> CFloat -> Int32 -> IO ()
-- | Draw an image, scaled, on the screen.
drawImageScaled :: Word32 -> Int32 -> Int32 -> CFloat -> CFloat -> CFloat -> CFloat -> Int32 -> IO ()
drawImageScaled src posX posY scaleX scaleY offsetX offsetY filter = c_drawImageScaled src posX posY scaleX scaleY offsetX offsetY filter

foreign import ccall unsafe "draw_text" c_drawText :: Word32 -> CString -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw some text on the screen.
drawText :: Word32 -> String -> Int32 -> Int32 -> Color -> IO ()
drawText font text posX posY color =
  withCString text $ \text_c ->
  with color $ \color_p ->
    c_drawText font text_c posX posY color_p

foreign import ccall unsafe "save_image" c_saveImage :: Word32 -> CString -> IO ()
-- | Save an image to persistant storage.
saveImage :: Word32 -> String -> IO ()
saveImage image filename =
  withCString filename $ \filename_c ->
    c_saveImage image filename_c

foreign import ccall unsafe "load_image" c_loadImage :: CString -> IO Word32
-- | Load an image from a file in cart.
loadImage :: String -> IO Word32
loadImage filename =
  withCString filename $ \filename_c ->
    c_loadImage filename_c

foreign import ccall unsafe "image_resize" c_imageResize :: Word32 -> Int32 -> Int32 -> Int32 -> IO Word32
-- | Resize an image, return copy.
imageResize :: Word32 -> Int32 -> Int32 -> Int32 -> IO Word32
imageResize image newWidth newHeight filter = c_imageResize image newWidth newHeight filter

foreign import ccall unsafe "image_scale" c_imageScale :: Word32 -> CFloat -> CFloat -> Int32 -> IO Word32
-- | Scale an image, return copy.
imageScale :: Word32 -> CFloat -> CFloat -> Int32 -> IO Word32
imageScale image scaleX scaleY filter = c_imageScale image scaleX scaleY filter

foreign import ccall unsafe "image_color_replace" c_imageColorReplace :: Word32 -> Ptr Color -> Ptr Color -> IO ()
-- | Replace a color in an image, in-place.
imageColorReplace :: Word32 -> Color -> Color -> IO ()
imageColorReplace image color replace =
  with color $ \color_p ->
  with replace $ \replace_p ->
    c_imageColorReplace image color_p replace_p

foreign import ccall unsafe "image_color_tint" c_imageColorTint :: Word32 -> Ptr Color -> IO ()
-- | Tint a color in an image, in-place.
imageColorTint :: Word32 -> Color -> IO ()
imageColorTint image color =
  with color $ \color_p ->
    c_imageColorTint image color_p

foreign import ccall unsafe "image_color_fade" c_imageColorFade :: Word32 -> CFloat -> IO ()
-- | Fade a color in an image, in-place.
imageColorFade :: Word32 -> CFloat -> IO ()
imageColorFade image alpha = c_imageColorFade image alpha

foreign import ccall unsafe "font_copy" c_fontCopy :: Word32 -> IO Word32
-- | Copy a font to a new font.
fontCopy :: Word32 -> IO Word32
fontCopy font = c_fontCopy font

foreign import ccall unsafe "font_scale" c_fontScale :: Word32 -> CFloat -> CFloat -> Int32 -> IO Word32
-- | Scale a font, return a new font.
fontScale :: Word32 -> CFloat -> CFloat -> Int32 -> IO Word32
fontScale font scaleX scaleY filter = c_fontScale font scaleX scaleY filter

foreign import ccall unsafe "load_font_bmf" c_loadFontBmf :: CString -> CString -> IO Word32
-- | Load a BMF font from a file in cart.
loadFontBmf :: String -> String -> IO Word32
loadFontBmf filename characters =
  withCString filename $ \filename_c ->
  withCString characters $ \characters_c ->
    c_loadFontBmf filename_c characters_c

foreign import ccall unsafe "load_font_bmf_from_image" c_loadFontBmfFromImage :: Word32 -> CString -> IO Word32
-- | Load a BMF font from an image.
loadFontBmfFromImage :: Word32 -> String -> IO Word32
loadFontBmfFromImage image characters =
  withCString characters $ \characters_c ->
    c_loadFontBmfFromImage image characters_c

foreign import ccall unsafe "measure_text" c_measureText :: Word32 -> CString -> Int32 -> IO (Ptr Dimensions)
-- | Measure the size of some text.
measureText :: Word32 -> String -> Int32 -> IO Dimensions
measureText font text textLength =
  withCString text $ \text_c ->
    c_measureText font text_c textLength >>= peek

foreign import ccall unsafe "measure_image" c_measureImage :: Word32 -> IO (Ptr Dimensions)
-- | Meaure an image (use 0 for screen).
measureImage :: Word32 -> IO Dimensions
measureImage image = c_measureImage image >>= peek

foreign import ccall unsafe "load_font_tty" c_loadFontTty :: CString -> Int32 -> Int32 -> CString -> IO Word32
-- | Load a TTY font from a file in cart.
loadFontTty :: String -> Int32 -> Int32 -> String -> IO Word32
loadFontTty filename glyphWidth glyphHeight characters =
  withCString filename $ \filename_c ->
  withCString characters $ \characters_c ->
    c_loadFontTty filename_c glyphWidth glyphHeight characters_c

foreign import ccall unsafe "load_font_tty_from_image" c_loadFontTtyFromImage :: Word32 -> Int32 -> Int32 -> CString -> IO Word32
-- | Load a TTY font from an image.
loadFontTtyFromImage :: Word32 -> Int32 -> Int32 -> String -> IO Word32
loadFontTtyFromImage image glyphWidth glyphHeight characters =
  withCString characters $ \characters_c ->
    c_loadFontTtyFromImage image glyphWidth glyphHeight characters_c

foreign import ccall unsafe "load_font_ttf" c_loadFontTtf :: CString -> Int32 -> IO Word32
-- | Load a TTF font from a file in cart.
loadFontTtf :: String -> Int32 -> IO Word32
loadFontTtf filename fontSize =
  withCString filename $ \filename_c ->
    c_loadFontTtf filename_c fontSize

foreign import ccall unsafe "image_color_invert" c_imageColorInvert :: Word32 -> IO ()
-- | Invert the colors in an image, in-place.
imageColorInvert :: Word32 -> IO ()
imageColorInvert image = c_imageColorInvert image

foreign import ccall unsafe "image_alpha_border" c_imageAlphaBorder :: Word32 -> CFloat -> IO (Ptr Rectangle)
-- | Calculate a rectangle representing the available alpha border in an image.
imageAlphaBorder :: Word32 -> CFloat -> IO Rectangle
imageAlphaBorder image threshold = c_imageAlphaBorder image threshold >>= peek

foreign import ccall unsafe "image_crop" c_imageCrop :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> IO ()
-- | Crop an image, in-place.
imageCrop :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> IO ()
imageCrop image x y width height = c_imageCrop image x y width height

foreign import ccall unsafe "image_alpha_crop" c_imageAlphaCrop :: Word32 -> CFloat -> IO ()
-- | Crop an image based on the alpha border, in-place.
imageAlphaCrop :: Word32 -> CFloat -> IO ()
imageAlphaCrop image threshold = c_imageAlphaCrop image threshold

foreign import ccall unsafe "image_color_brightness" c_imageColorBrightness :: Word32 -> CFloat -> IO ()
-- | Adjust the brightness of an image, in-place.
imageColorBrightness :: Word32 -> CFloat -> IO ()
imageColorBrightness image factor = c_imageColorBrightness image factor

foreign import ccall unsafe "image_flip" c_imageFlip :: Word32 -> CBool -> CBool -> IO ()
-- | Flip an image, in-place.
imageFlip :: Word32 -> Bool -> Bool -> IO ()
imageFlip image horizontal vertical = c_imageFlip image (fromBool horizontal) (fromBool vertical)

foreign import ccall unsafe "image_color_contrast" c_imageColorContrast :: Word32 -> CFloat -> IO ()
-- | Change the contrast of an image, in-place.
imageColorContrast :: Word32 -> CFloat -> IO ()
imageColorContrast image contrast = c_imageColorContrast image contrast

foreign import ccall unsafe "image_alpha_mask" c_imageAlphaMask :: Word32 -> Word32 -> Int32 -> Int32 -> IO ()
-- | Use an image as an alpha-mask on another image.
imageAlphaMask :: Word32 -> Word32 -> Int32 -> Int32 -> IO ()
imageAlphaMask image alphaMask posX posY = c_imageAlphaMask image alphaMask posX posY

foreign import ccall unsafe "image_rotate" c_imageRotate :: Word32 -> CFloat -> Int32 -> IO Word32
-- | Create a new image, rotating another image.
imageRotate :: Word32 -> CFloat -> Int32 -> IO Word32
imageRotate image degrees filter = c_imageRotate image degrees filter

foreign import ccall unsafe "image_gradient" c_imageGradient :: Int32 -> Int32 -> Ptr Color -> Ptr Color -> Ptr Color -> Ptr Color -> IO Word32
-- | Create a new image of a gradient.
imageGradient :: Int32 -> Int32 -> Color -> Color -> Color -> Color -> IO Word32
imageGradient width height topLeft topRight bottomLeft bottomRight =
  with topLeft $ \topLeft_p ->
  with topRight $ \topRight_p ->
  with bottomLeft $ \bottomLeft_p ->
  with bottomRight $ \bottomRight_p ->
    c_imageGradient width height topLeft_p topRight_p bottomLeft_p bottomRight_p

foreign import ccall unsafe "unload_image" c_unloadImage :: Word32 -> IO ()
-- | Unload an image.
unloadImage :: Word32 -> IO ()
unloadImage image = c_unloadImage image

foreign import ccall unsafe "unload_font" c_unloadFont :: Word32 -> IO ()
-- | Unload a font.
unloadFont :: Word32 -> IO ()
unloadFont font = c_unloadFont font

foreign import ccall unsafe "clear_image" c_clearImage :: Word32 -> Ptr Color -> IO ()
-- | Clear an image.
clearImage :: Word32 -> Color -> IO ()
clearImage destination color =
  with color $ \color_p ->
    c_clearImage destination color_p

foreign import ccall unsafe "draw_point_on_image" c_drawPointOnImage :: Word32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a single pixel on an image.
drawPointOnImage :: Word32 -> Int32 -> Int32 -> Color -> IO ()
drawPointOnImage destination x y color =
  with color $ \color_p ->
    c_drawPointOnImage destination x y color_p

foreign import ccall unsafe "draw_line_on_image" c_drawLineOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a line on an image.
drawLineOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
drawLineOnImage destination startPosX startPosY endPosX endPosY color =
  with color $ \color_p ->
    c_drawLineOnImage destination startPosX startPosY endPosX endPosY color_p

foreign import ccall unsafe "draw_rectangle_on_image" c_drawRectangleOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a filled rectangle on an image.
drawRectangleOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
drawRectangleOnImage destination posX posY width height color =
  with color $ \color_p ->
    c_drawRectangleOnImage destination posX posY width height color_p

foreign import ccall unsafe "draw_triangle_on_image" c_drawTriangleOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a filled triangle on an image.
drawTriangleOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
drawTriangleOnImage destination x1 y1 x2 y2 x3 y3 color =
  with color $ \color_p ->
    c_drawTriangleOnImage destination x1 y1 x2 y2 x3 y3 color_p

foreign import ccall unsafe "draw_ellipse_on_image" c_drawEllipseOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a filled ellipse on an image.
drawEllipseOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
drawEllipseOnImage destination centerX centerY radiusX radiusY color =
  with color $ \color_p ->
    c_drawEllipseOnImage destination centerX centerY radiusX radiusY color_p

foreign import ccall unsafe "draw_circle_on_image" c_drawCircleOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a circle on an image.
drawCircleOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
drawCircleOnImage destination centerX centerY radius color =
  with color $ \color_p ->
    c_drawCircleOnImage destination centerX centerY radius color_p

foreign import ccall unsafe "draw_polygon_on_image" c_drawPolygonOnImage :: Word32 -> Ptr Vector -> Word32 -> Ptr Color -> IO ()
-- | Draw a filled polygon on an image.
drawPolygonOnImage :: Word32 -> [Vector] -> Color -> IO ()
drawPolygonOnImage destination points color =
  withArrayLen points $ \points_count points_ptr ->
  with color $ \color_p ->
    c_drawPolygonOnImage destination points_ptr (fromIntegral points_count) color_p

foreign import ccall unsafe "draw_rectangle_rounded_on_image" c_drawRectangleRoundedOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a filled round-rectangle on an image.
drawRectangleRoundedOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
drawRectangleRoundedOnImage destination x y width height cornerRadius color =
  with color $ \color_p ->
    c_drawRectangleRoundedOnImage destination x y width height cornerRadius color_p

foreign import ccall unsafe "draw_image_on_image" c_drawImageOnImage :: Word32 -> Word32 -> Int32 -> Int32 -> IO ()
-- | Draw an image on an image.
drawImageOnImage :: Word32 -> Word32 -> Int32 -> Int32 -> IO ()
drawImageOnImage destination src posX posY = c_drawImageOnImage destination src posX posY

foreign import ccall unsafe "draw_image_tint_on_image" c_drawImageTintOnImage :: Word32 -> Word32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a tinted image on an image.
drawImageTintOnImage :: Word32 -> Word32 -> Int32 -> Int32 -> Color -> IO ()
drawImageTintOnImage destination src posX posY tint =
  with tint $ \tint_p ->
    c_drawImageTintOnImage destination src posX posY tint_p

foreign import ccall unsafe "draw_image_rotated_on_image" c_drawImageRotatedOnImage :: Word32 -> Word32 -> Int32 -> Int32 -> CFloat -> CFloat -> CFloat -> Int32 -> IO ()
-- | Draw an image, rotated, on an image.
drawImageRotatedOnImage :: Word32 -> Word32 -> Int32 -> Int32 -> CFloat -> CFloat -> CFloat -> Int32 -> IO ()
drawImageRotatedOnImage destination src posX posY degrees offsetX offsetY filter = c_drawImageRotatedOnImage destination src posX posY degrees offsetX offsetY filter

foreign import ccall unsafe "draw_image_flipped_on_image" c_drawImageFlippedOnImage :: Word32 -> Word32 -> Int32 -> Int32 -> CBool -> CBool -> CBool -> IO ()
-- | Draw an image, flipped, on an image.
drawImageFlippedOnImage :: Word32 -> Word32 -> Int32 -> Int32 -> Bool -> Bool -> Bool -> IO ()
drawImageFlippedOnImage destination src posX posY flipHorizontal flipVertical flipDiagonal = c_drawImageFlippedOnImage destination src posX posY (fromBool flipHorizontal) (fromBool flipVertical) (fromBool flipDiagonal)

foreign import ccall unsafe "draw_image_scaled_on_image" c_drawImageScaledOnImage :: Word32 -> Word32 -> Int32 -> Int32 -> CFloat -> CFloat -> CFloat -> CFloat -> Int32 -> IO ()
-- | Draw an image, scaled, on an image.
drawImageScaledOnImage :: Word32 -> Word32 -> Int32 -> Int32 -> CFloat -> CFloat -> CFloat -> CFloat -> Int32 -> IO ()
drawImageScaledOnImage destination src posX posY scaleX scaleY offsetX offsetY filter = c_drawImageScaledOnImage destination src posX posY scaleX scaleY offsetX offsetY filter

foreign import ccall unsafe "draw_text_on_image" c_drawTextOnImage :: Word32 -> Word32 -> CString -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw some text on an image.
drawTextOnImage :: Word32 -> Word32 -> String -> Int32 -> Int32 -> Color -> IO ()
drawTextOnImage destination font text posX posY color =
  withCString text $ \text_c ->
  with color $ \color_p ->
    c_drawTextOnImage destination font text_c posX posY color_p

foreign import ccall unsafe "draw_rectangle_outline" c_drawRectangleOutline :: Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a outlined (with thickness) rectangle on the screen.
drawRectangleOutline :: Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
drawRectangleOutline posX posY width height thickness color =
  with color $ \color_p ->
    c_drawRectangleOutline posX posY width height thickness color_p

foreign import ccall unsafe "draw_triangle_outline" c_drawTriangleOutline :: Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a outlined (with thickness) triangle on the screen.
drawTriangleOutline :: Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
drawTriangleOutline x1 y1 x2 y2 x3 y3 thickness color =
  with color $ \color_p ->
    c_drawTriangleOutline x1 y1 x2 y2 x3 y3 thickness color_p

foreign import ccall unsafe "draw_ellipse_outline" c_drawEllipseOutline :: Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a outlined (with thickness) ellipse on the screen.
drawEllipseOutline :: Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
drawEllipseOutline centerX centerY radiusX radiusY thickness color =
  with color $ \color_p ->
    c_drawEllipseOutline centerX centerY radiusX radiusY thickness color_p

foreign import ccall unsafe "draw_circle_outline" c_drawCircleOutline :: Int32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a outlined (with thickness) circle on the screen.
drawCircleOutline :: Int32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
drawCircleOutline centerX centerY radius thickness color =
  with color $ \color_p ->
    c_drawCircleOutline centerX centerY radius thickness color_p

foreign import ccall unsafe "draw_polygon_outline" c_drawPolygonOutline :: Ptr Vector -> Word32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a outlined (with thickness) polygon on the screen.
drawPolygonOutline :: [Vector] -> Int32 -> Color -> IO ()
drawPolygonOutline points thickness color =
  withArrayLen points $ \points_count points_ptr ->
  with color $ \color_p ->
    c_drawPolygonOutline points_ptr (fromIntegral points_count) thickness color_p

foreign import ccall unsafe "draw_arc_outline" c_drawArcOutline :: Int32 -> Int32 -> CFloat -> CFloat -> CFloat -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a outlined (with thickness) arc on the screen.
drawArcOutline :: Int32 -> Int32 -> CFloat -> CFloat -> CFloat -> Int32 -> Int32 -> Color -> IO ()
drawArcOutline centerX centerY radius startAngle endAngle segments thickness color =
  with color $ \color_p ->
    c_drawArcOutline centerX centerY radius startAngle endAngle segments thickness color_p

foreign import ccall unsafe "draw_rectangle_rounded_outline" c_drawRectangleRoundedOutline :: Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a outlined (with thickness) round-rectangle on the screen.
drawRectangleRoundedOutline :: Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
drawRectangleRoundedOutline x y width height cornerRadius thickness color =
  with color $ \color_p ->
    c_drawRectangleRoundedOutline x y width height cornerRadius thickness color_p

foreign import ccall unsafe "draw_rectangle_outline_on_image" c_drawRectangleOutlineOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a outlined (with thickness) rectangle on an image.
drawRectangleOutlineOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
drawRectangleOutlineOnImage destination posX posY width height thickness color =
  with color $ \color_p ->
    c_drawRectangleOutlineOnImage destination posX posY width height thickness color_p

foreign import ccall unsafe "draw_triangle_outline_on_image" c_drawTriangleOutlineOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a outlined (with thickness) triangle on an image.
drawTriangleOutlineOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
drawTriangleOutlineOnImage destination x1 y1 x2 y2 x3 y3 thickness color =
  with color $ \color_p ->
    c_drawTriangleOutlineOnImage destination x1 y1 x2 y2 x3 y3 thickness color_p

foreign import ccall unsafe "draw_ellipse_outline_on_image" c_drawEllipseOutlineOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a outlined (with thickness) ellipse on an image.
drawEllipseOutlineOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
drawEllipseOutlineOnImage destination centerX centerY radiusX radiusY thickness color =
  with color $ \color_p ->
    c_drawEllipseOutlineOnImage destination centerX centerY radiusX radiusY thickness color_p

foreign import ccall unsafe "draw_circle_outline_on_image" c_drawCircleOutlineOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a outlined (with thickness) circle on an image.
drawCircleOutlineOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
drawCircleOutlineOnImage destination centerX centerY radius thickness color =
  with color $ \color_p ->
    c_drawCircleOutlineOnImage destination centerX centerY radius thickness color_p

foreign import ccall unsafe "draw_polygon_outline_on_image" c_drawPolygonOutlineOnImage :: Word32 -> Ptr Vector -> Word32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a outlined (with thickness) polygon on an image.
drawPolygonOutlineOnImage :: Word32 -> [Vector] -> Int32 -> Color -> IO ()
drawPolygonOutlineOnImage destination points thickness color =
  withArrayLen points $ \points_count points_ptr ->
  with color $ \color_p ->
    c_drawPolygonOutlineOnImage destination points_ptr (fromIntegral points_count) thickness color_p

foreign import ccall unsafe "draw_rectangle_rounded_outline_on_image" c_drawRectangleRoundedOutlineOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a outlined (with thickness) round-rectangle on an image.
drawRectangleRoundedOutlineOnImage :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
drawRectangleRoundedOutlineOnImage destination x y width height cornerRadius thickness color =
  with color $ \color_p ->
    c_drawRectangleRoundedOutlineOnImage destination x y width height cornerRadius thickness color_p

-- GUI

foreign import ccall unsafe "gui_begin_window" c_guiBeginWindow :: CString -> Ptr Rectangle -> IO CBool
-- | Begin a GUI window. Returns false if the window is collapsed or closed - skip its contents, but still call gui_end_window.
guiBeginWindow :: String -> Rectangle -> IO Bool
guiBeginWindow title rect =
  withCString title $ \title_c ->
  with rect $ \rect_p ->
    toBool <$> c_guiBeginWindow title_c rect_p

foreign import ccall unsafe "gui_end_window" c_guiEndWindow :: IO ()
-- | End the current GUI window.
guiEndWindow :: IO ()
guiEndWindow = c_guiEndWindow

foreign import ccall unsafe "gui_button" c_guiButton :: CString -> IO CBool
-- | A button. Returns true when it is clicked.
guiButton :: String -> IO Bool
guiButton label =
  withCString label $ \label_c ->
    toBool <$> c_guiButton label_c

foreign import ccall unsafe "gui_label" c_guiLabel :: CString -> IO ()
-- | A static text label.
guiLabel :: String -> IO ()
guiLabel text =
  withCString text $ \text_c ->
    c_guiLabel text_c

foreign import ccall unsafe "gui_text" c_guiText :: CString -> IO ()
-- | A block of wrapping text.
guiText :: String -> IO ()
guiText text =
  withCString text $ \text_c ->
    c_guiText text_c

foreign import ccall unsafe "gui_checkbox" c_guiCheckbox :: CString -> CBool -> IO CBool
-- | A checkbox. Returns the (possibly changed) state.
guiCheckbox :: String -> Bool -> IO Bool
guiCheckbox label state =
  withCString label $ \label_c ->
    toBool <$> c_guiCheckbox label_c (fromBool state)

foreign import ccall unsafe "gui_slider" c_guiSlider :: CFloat -> CFloat -> CFloat -> IO CFloat
-- | A slider. Returns the (possibly changed) value.
guiSlider :: CFloat -> CFloat -> CFloat -> IO CFloat
guiSlider value low high = c_guiSlider value low high

foreign import ccall unsafe "gui_layout_row" c_guiLayoutRow :: Ptr Int32 -> Word32 -> Int32 -> IO ()
-- | Set the current layout row - the column widths (negative for flexible), and the row height.
guiLayoutRow :: [Int32] -> Int32 -> IO ()
guiLayoutRow widths height =
  withArrayLen widths $ \widths_count widths_ptr ->
    c_guiLayoutRow widths_ptr (fromIntegral widths_count) height

foreign import ccall unsafe "gui_end" c_guiEnd :: IO ()
-- | Finish building the GUI for this frame. Called automatically at the end of update if you do not call it.
guiEnd :: IO ()
guiEnd = c_guiEnd

foreign import ccall unsafe "gui_draw" c_guiDraw :: Word32 -> IO ()
-- | Draw the GUI to an image (0 is the screen).
guiDraw :: Word32 -> IO ()
guiDraw dst = c_guiDraw dst

-- INPUT

foreign import ccall unsafe "key_pressed" c_keyPressed :: Int32 -> IO CBool
-- | Has the key been pressed? (tracks unpress/read correctly.)
keyPressed :: Int32 -> IO Bool
keyPressed key = toBool <$> c_keyPressed key

foreign import ccall unsafe "key_down" c_keyDown :: Int32 -> IO CBool
-- | Is the key currently down?
keyDown :: Int32 -> IO Bool
keyDown key = toBool <$> c_keyDown key

foreign import ccall unsafe "key_released" c_keyReleased :: Int32 -> IO CBool
-- | Has the key been released? (tracks press/read correctly.)
keyReleased :: Int32 -> IO Bool
keyReleased key = toBool <$> c_keyReleased key

foreign import ccall unsafe "key_up" c_keyUp :: Int32 -> IO CBool
-- | Is the key currently up?
keyUp :: Int32 -> IO Bool
keyUp key = toBool <$> c_keyUp key

foreign import ccall unsafe "gamepad_button_pressed" c_gamepadButtonPressed :: Int32 -> Int32 -> IO CBool
-- | Has the button been pressed? (tracks unpress/read correctly.)
gamepadButtonPressed :: Int32 -> Int32 -> IO Bool
gamepadButtonPressed gamepad button = toBool <$> c_gamepadButtonPressed gamepad button

foreign import ccall unsafe "gamepad_button_down" c_gamepadButtonDown :: Int32 -> Int32 -> IO CBool
-- | Is the button currently down?
gamepadButtonDown :: Int32 -> Int32 -> IO Bool
gamepadButtonDown gamepad button = toBool <$> c_gamepadButtonDown gamepad button

foreign import ccall unsafe "gamepad_button_released" c_gamepadButtonReleased :: Int32 -> Int32 -> IO CBool
-- | Has the button been released? (tracks press/read correctly.)
gamepadButtonReleased :: Int32 -> Int32 -> IO Bool
gamepadButtonReleased gamepad button = toBool <$> c_gamepadButtonReleased gamepad button

foreign import ccall unsafe "mouse_position" c_mousePosition :: IO (Ptr Vector)
-- | Get current position of mouse.
mousePosition :: IO Vector
mousePosition = c_mousePosition >>= peek

foreign import ccall unsafe "mouse_button_pressed" c_mouseButtonPressed :: Int32 -> IO CBool
-- | Has the button been pressed? (tracks unpress/read correctly.)
mouseButtonPressed :: Int32 -> IO Bool
mouseButtonPressed button = toBool <$> c_mouseButtonPressed button

foreign import ccall unsafe "mouse_button_down" c_mouseButtonDown :: Int32 -> IO CBool
-- | Is the button currently down?
mouseButtonDown :: Int32 -> IO Bool
mouseButtonDown button = toBool <$> c_mouseButtonDown button

foreign import ccall unsafe "mouse_button_released" c_mouseButtonReleased :: Int32 -> IO CBool
-- | Has the button been released? (tracks press/read correctly.)
mouseButtonReleased :: Int32 -> IO Bool
mouseButtonReleased button = toBool <$> c_mouseButtonReleased button

foreign import ccall unsafe "mouse_button_up" c_mouseButtonUp :: Int32 -> IO CBool
-- | Is the button currently up?
mouseButtonUp :: Int32 -> IO Bool
mouseButtonUp button = toBool <$> c_mouseButtonUp button

-- SOUND

foreign import ccall unsafe "load_sound" c_loadSound :: CString -> IO Word32
-- | Load a sound from a file in cart.
loadSound :: String -> IO Word32
loadSound filename =
  withCString filename $ \filename_c ->
    c_loadSound filename_c

foreign import ccall unsafe "play_sound" c_playSound :: Word32 -> CBool -> IO ()
-- | Play a sound.
playSound :: Word32 -> Bool -> IO ()
playSound sound loop = c_playSound sound (fromBool loop)

foreign import ccall unsafe "stop_sound" c_stopSound :: Word32 -> IO ()
-- | Stop a sound.
stopSound :: Word32 -> IO ()
stopSound sound = c_stopSound sound

foreign import ccall unsafe "unload_sound" c_unloadSound :: Word32 -> IO ()
-- | Unload a sound.
unloadSound :: Word32 -> IO ()
unloadSound sound = c_unloadSound sound

foreign import ccall unsafe "tts_sound" c_ttsSound :: CString -> CBool -> Int32 -> Int32 -> Int32 -> Int32 -> CBool -> IO Word32
-- | Speak some text and return a sound. Set things to 0 for defaults.
ttsSound :: String -> Bool -> Int32 -> Int32 -> Int32 -> Int32 -> Bool -> IO Word32
ttsSound text phonetic pitch speed throat mouth sing =
  withCString text $ \text_c ->
    c_ttsSound text_c (fromBool phonetic) pitch speed throat mouth (fromBool sing)

foreign import ccall unsafe "sfx_sound" c_sfxSound :: Ptr SfxParams -> IO Word32
-- | Create Sfx sound.
sfxSound :: SfxParams -> IO Word32
sfxSound params =
  with params $ \params_p ->
    c_sfxSound params_p

foreign import ccall unsafe "sfx_generate" c_sfxGenerate :: Int32 -> IO (Ptr SfxParams)
-- | Create Sfx parameters.
sfxGenerate :: Int32 -> IO SfxParams
sfxGenerate type_ = c_sfxGenerate type_ >>= peek

-- TILE

foreign import ccall unsafe "load_tilemap" c_loadTilemap :: CString -> IO Word32
-- | Load a tilemap (a Tiled map, exported as JSON) from a file in cart.
loadTilemap :: String -> IO Word32
loadTilemap filename =
  withCString filename $ \filename_c ->
    c_loadTilemap filename_c

foreign import ccall unsafe "unload_tilemap" c_unloadTilemap :: Word32 -> IO ()
-- | Unload a tilemap.
unloadTilemap :: Word32 -> IO ()
unloadTilemap tilemap = c_unloadTilemap tilemap

foreign import ccall unsafe "tile_update" c_tileUpdate :: Word32 -> CFloat -> IO ()
-- | Update a tilemap's animation timers (deltaTime is in seconds).
tileUpdate :: Word32 -> CFloat -> IO ()
tileUpdate tilemap deltaTime = c_tileUpdate tilemap deltaTime

foreign import ccall unsafe "tile_map_size" c_tileMapSize :: Word32 -> IO (Ptr Dimensions)
-- | Get the size of a tilemap, in tiles.
tileMapSize :: Word32 -> IO Dimensions
tileMapSize tilemap = c_tileMapSize tilemap >>= peek

foreign import ccall unsafe "tile_tile_size" c_tileTileSize :: Word32 -> IO (Ptr Dimensions)
-- | Get the size of a single tile of a tilemap, in pixels.
tileTileSize :: Word32 -> IO Dimensions
tileTileSize tilemap = c_tileTileSize tilemap >>= peek

foreign import ccall unsafe "tile_map_prop" c_tileMapProp :: Word32 -> CString -> IO (Ptr TilemapProp)
-- | Get a custom property of a tilemap, by name (PROP_NONE when there is no such property.)
tileMapProp :: Word32 -> String -> IO TilemapProp
tileMapProp tilemap name =
  withCString name $ \name_c ->
    c_tileMapProp tilemap name_c >>= peek

foreign import ccall unsafe "tile_map_prop_count" c_tileMapPropCount :: Word32 -> IO Int32
-- | Get the number of custom properties on a tilemap.
tileMapPropCount :: Word32 -> IO Int32
tileMapPropCount tilemap = c_tileMapPropCount tilemap

foreign import ccall unsafe "tile_map_prop_at" c_tileMapPropAt :: Word32 -> Int32 -> IO (Ptr TilemapProp)
-- | Get a custom property of a tilemap, by index (PROP_NONE when out of range.)
tileMapPropAt :: Word32 -> Int32 -> IO TilemapProp
tileMapPropAt tilemap index = c_tileMapPropAt tilemap index >>= peek

foreign import ccall unsafe "tile_draw" c_tileDraw :: Word32 -> Int32 -> Int32 -> IO ()
-- | Draw a tilemap on the screen.
tileDraw :: Word32 -> Int32 -> Int32 -> IO ()
tileDraw tilemap posX posY = c_tileDraw tilemap posX posY

foreign import ccall unsafe "tile_draw_tint" c_tileDrawTint :: Word32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a tilemap on the screen, tinted by a color.
tileDrawTint :: Word32 -> Int32 -> Int32 -> Color -> IO ()
tileDrawTint tilemap posX posY tint =
  with tint $ \tint_p ->
    c_tileDrawTint tilemap posX posY tint_p

foreign import ccall unsafe "tile_draw_on_image" c_tileDrawOnImage :: Word32 -> Word32 -> Int32 -> Int32 -> IO ()
-- | Draw a tilemap on an image.
tileDrawOnImage :: Word32 -> Word32 -> Int32 -> Int32 -> IO ()
tileDrawOnImage dst tilemap posX posY = c_tileDrawOnImage dst tilemap posX posY

foreign import ccall unsafe "tilemap_image" c_tilemapImage :: Word32 -> IO Word32
-- | Render a whole tilemap to a new image.
tilemapImage :: Word32 -> IO Word32
tilemapImage tilemap = c_tilemapImage tilemap

foreign import ccall unsafe "tile_layer_count" c_tileLayerCount :: Word32 -> IO Int32
-- | Get the number of layers in a tilemap. Layers are numbered depth-first, so the children of a group layer have their own indexes too.
tileLayerCount :: Word32 -> IO Int32
tileLayerCount tilemap = c_tileLayerCount tilemap

foreign import ccall unsafe "tile_layer_index" c_tileLayerIndex :: Word32 -> CString -> IO Int32
-- | Get the index of a layer of a tilemap, by name (-1 when there is no such layer.)
tileLayerIndex :: Word32 -> String -> IO Int32
tileLayerIndex tilemap name =
  withCString name $ \name_c ->
    c_tileLayerIndex tilemap name_c

foreign import ccall unsafe "tile_layer_name" c_tileLayerName :: Word32 -> Int32 -> IO CString
-- | Get the name of a layer of a tilemap.
tileLayerName :: Word32 -> Int32 -> IO String
tileLayerName tilemap layer = c_tileLayerName tilemap layer >>= peekCString

foreign import ccall unsafe "tile_layer_type" c_tileLayerType :: Word32 -> Int32 -> IO Int32
-- | Get the kind of a layer of a tilemap.
tileLayerType :: Word32 -> Int32 -> IO Int32
tileLayerType tilemap layer = c_tileLayerType tilemap layer

foreign import ccall unsafe "tile_layer_size" c_tileLayerSize :: Word32 -> Int32 -> IO (Ptr Dimensions)
-- | Get the size of a layer of a tilemap, in tiles.
tileLayerSize :: Word32 -> Int32 -> IO Dimensions
tileLayerSize tilemap layer = c_tileLayerSize tilemap layer >>= peek

foreign import ccall unsafe "tile_layer_visible" c_tileLayerVisible :: Word32 -> Int32 -> IO CBool
-- | Get whether a layer of a tilemap is visible. Drawing a layer that Tiled marked hidden draws nothing.
tileLayerVisible :: Word32 -> Int32 -> IO Bool
tileLayerVisible tilemap layer = toBool <$> c_tileLayerVisible tilemap layer

foreign import ccall unsafe "tile_layer_prop" c_tileLayerProp :: Word32 -> Int32 -> CString -> IO (Ptr TilemapProp)
-- | Get a custom property of a layer of a tilemap, by name (PROP_NONE when there is no such property.)
tileLayerProp :: Word32 -> Int32 -> String -> IO TilemapProp
tileLayerProp tilemap layer name =
  withCString name $ \name_c ->
    c_tileLayerProp tilemap layer name_c >>= peek

foreign import ccall unsafe "tile_layer_prop_count" c_tileLayerPropCount :: Word32 -> Int32 -> IO Int32
-- | Get the number of custom properties on a layer of a tilemap.
tileLayerPropCount :: Word32 -> Int32 -> IO Int32
tileLayerPropCount tilemap layer = c_tileLayerPropCount tilemap layer

foreign import ccall unsafe "tile_layer_prop_at" c_tileLayerPropAt :: Word32 -> Int32 -> Int32 -> IO (Ptr TilemapProp)
-- | Get a custom property of a layer of a tilemap, by index (PROP_NONE when out of range.)
tileLayerPropAt :: Word32 -> Int32 -> Int32 -> IO TilemapProp
tileLayerPropAt tilemap layer index = c_tileLayerPropAt tilemap layer index >>= peek

foreign import ccall unsafe "tile_draw_layer" c_tileDrawLayer :: Word32 -> Int32 -> Int32 -> Int32 -> IO ()
-- | Draw a single layer of a tilemap on the screen.
tileDrawLayer :: Word32 -> Int32 -> Int32 -> Int32 -> IO ()
tileDrawLayer tilemap layer posX posY = c_tileDrawLayer tilemap layer posX posY

foreign import ccall unsafe "tile_draw_layer_tint" c_tileDrawLayerTint :: Word32 -> Int32 -> Int32 -> Int32 -> Ptr Color -> IO ()
-- | Draw a single layer of a tilemap on the screen, tinted by a color.
tileDrawLayerTint :: Word32 -> Int32 -> Int32 -> Int32 -> Color -> IO ()
tileDrawLayerTint tilemap layer posX posY tint =
  with tint $ \tint_p ->
    c_tileDrawLayerTint tilemap layer posX posY tint_p

foreign import ccall unsafe "tile_draw_layer_on_image" c_tileDrawLayerOnImage :: Word32 -> Word32 -> Int32 -> Int32 -> Int32 -> IO ()
-- | Draw a single layer of a tilemap on an image.
tileDrawLayerOnImage :: Word32 -> Word32 -> Int32 -> Int32 -> Int32 -> IO ()
tileDrawLayerOnImage dst tilemap layer posX posY = c_tileDrawLayerOnImage dst tilemap layer posX posY

foreign import ccall unsafe "tile_layer_image" c_tileLayerImage :: Word32 -> Int32 -> IO Word32
-- | Render a single layer of a tilemap to a new image.
tileLayerImage :: Word32 -> Int32 -> IO Word32
tileLayerImage tilemap layer = c_tileLayerImage tilemap layer

foreign import ccall unsafe "tile_get_tile" c_tileGetTile :: Word32 -> Int32 -> Int32 -> Int32 -> IO Int32
-- | Get the gid of the tile at a column/row in a tilemap layer.
tileGetTile :: Word32 -> Int32 -> Int32 -> Int32 -> IO Int32
tileGetTile tilemap layer column row = c_tileGetTile tilemap layer column row

foreign import ccall unsafe "tile_set_tile" c_tileSetTile :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> IO ()
-- | Set the gid of the tile at a column/row in a tilemap layer. Swapping a gid is how a cart keeps changing state in the map itself.
tileSetTile :: Word32 -> Int32 -> Int32 -> Int32 -> Int32 -> IO ()
tileSetTile tilemap layer column row gid = c_tileSetTile tilemap layer column row gid

foreign import ccall unsafe "tile_draw_tile" c_tileDrawTile :: Word32 -> Int32 -> Int32 -> Int32 -> IO ()
-- | Draw a single tile from a tilemap on the screen.
tileDrawTile :: Word32 -> Int32 -> Int32 -> Int32 -> IO ()
tileDrawTile tilemap gid posX posY = c_tileDrawTile tilemap gid posX posY

foreign import ccall unsafe "tile_image" c_tileImage :: Word32 -> Int32 -> IO Word32
-- | Get a copy of the image of a single tile in a tilemap.
tileImage :: Word32 -> Int32 -> IO Word32
tileImage tilemap gid = c_tileImage tilemap gid

foreign import ccall unsafe "tile_gid_prop" c_tileGidProp :: Word32 -> Int32 -> CString -> IO (Ptr TilemapProp)
-- | Get a custom property of a tile of a tilemap, by name (PROP_NONE when there is no such property.) These come from the tileset, so every tile with this gid shares them.
tileGidProp :: Word32 -> Int32 -> String -> IO TilemapProp
tileGidProp tilemap gid name =
  withCString name $ \name_c ->
    c_tileGidProp tilemap gid name_c >>= peek

foreign import ccall unsafe "tile_gid_prop_count" c_tileGidPropCount :: Word32 -> Int32 -> IO Int32
-- | Get the number of custom properties on a tile of a tilemap.
tileGidPropCount :: Word32 -> Int32 -> IO Int32
tileGidPropCount tilemap gid = c_tileGidPropCount tilemap gid

foreign import ccall unsafe "tile_gid_prop_at" c_tileGidPropAt :: Word32 -> Int32 -> Int32 -> IO (Ptr TilemapProp)
-- | Get a custom property of a tile of a tilemap, by index (PROP_NONE when out of range.)
tileGidPropAt :: Word32 -> Int32 -> Int32 -> IO TilemapProp
tileGidPropAt tilemap gid index = c_tileGidPropAt tilemap gid index >>= peek

foreign import ccall unsafe "tile_object_count" c_tileObjectCount :: Word32 -> Int32 -> IO Int32
-- | Get the number of objects on an object-layer of a tilemap.
tileObjectCount :: Word32 -> Int32 -> IO Int32
tileObjectCount tilemap layer = c_tileObjectCount tilemap layer

foreign import ccall unsafe "tile_object" c_tileObject :: Word32 -> Int32 -> Int32 -> IO (Ptr TilemapObject)
-- | Get an object from an object-layer of a tilemap.
tileObject :: Word32 -> Int32 -> Int32 -> IO TilemapObject
tileObject tilemap layer index = c_tileObject tilemap layer index >>= peek

foreign import ccall unsafe "tile_object_index" c_tileObjectIndex :: Word32 -> Int32 -> CString -> IO Int32
-- | Get the index of an object on an object-layer of a tilemap, by name (-1 when there is no such object.)
tileObjectIndex :: Word32 -> Int32 -> String -> IO Int32
tileObjectIndex tilemap layer name =
  withCString name $ \name_c ->
    c_tileObjectIndex tilemap layer name_c

foreign import ccall unsafe "tile_object_prop" c_tileObjectProp :: Word32 -> Int32 -> Int32 -> CString -> IO (Ptr TilemapProp)
-- | Get a custom property of an object of a tilemap, by name (PROP_NONE when there is no such property.)
tileObjectProp :: Word32 -> Int32 -> Int32 -> String -> IO TilemapProp
tileObjectProp tilemap layer index name =
  withCString name $ \name_c ->
    c_tileObjectProp tilemap layer index name_c >>= peek

foreign import ccall unsafe "tile_object_prop_count" c_tileObjectPropCount :: Word32 -> Int32 -> Int32 -> IO Int32
-- | Get the number of custom properties on an object of a tilemap.
tileObjectPropCount :: Word32 -> Int32 -> Int32 -> IO Int32
tileObjectPropCount tilemap layer index = c_tileObjectPropCount tilemap layer index

foreign import ccall unsafe "tile_object_prop_at" c_tileObjectPropAt :: Word32 -> Int32 -> Int32 -> Int32 -> IO (Ptr TilemapProp)
-- | Get a custom property of an object of a tilemap, by index (PROP_NONE when out of range.)
tileObjectPropAt :: Word32 -> Int32 -> Int32 -> Int32 -> IO TilemapProp
tileObjectPropAt tilemap layer index propIndex = c_tileObjectPropAt tilemap layer index propIndex >>= peek

-- TYPES

-- UTILITIES

foreign import ccall unsafe "current_time" c_currentTime :: IO Word64
-- | Get system-time (ms) since unix epoch.
currentTime :: IO Word64
currentTime = c_currentTime

foreign import ccall unsafe "delta_time" c_deltaTime :: IO CFloat
-- | Get the change in time (seconds) since the last update run.
deltaTime :: IO CFloat
deltaTime = c_deltaTime

foreign import ccall unsafe "random_int" c_randomInt :: Int32 -> Int32 -> IO Int32
-- | Get a random integer between 2 numbers.
randomInt :: Int32 -> Int32 -> IO Int32
randomInt min max = c_randomInt min max

foreign import ccall unsafe "random_seed_get" c_randomSeedGet :: IO Word64
-- | Get the random-seed.
randomSeedGet :: IO Word64
randomSeedGet = c_randomSeedGet

foreign import ccall unsafe "random_seed_set" c_randomSeedSet :: Word64 -> IO ()
-- | Set the random-seed.
randomSeedSet :: Word64 -> IO ()
randomSeedSet seed = c_randomSeedSet seed

