// <null0-cart src="..."> - the simplest way to put a cart on a page.
//
// This file is published to https://notnullgames.github.io/null0/null0-cart.js
// and is meant to be used straight from there:
//
//   <script type="module" src="https://notnullgames.github.io/null0/null0-cart.js"></script>
//   <null0-cart src="https://notnullgames.github.io/null0/carts/simple_c.null0"></null0-cart>
//
// A cart's wasm instance is expensive and there is no way to fully tear one
// down, so a cart is only instantiated once it scrolls into view. A page with
// several carts on it therefore only pays for the ones actually looked at.
// Set loading="eager" to instantiate immediately instead.

import loadCart from './null0.js'

class Null0Cart extends HTMLElement {
  static get observedAttributes() {
    return ['src']
  }

  constructor() {
    super()
    const shadow = this.attachShadow({ mode: 'open' })
    const style = document.createElement('style')
    style.textContent = `
      :host { display: block; }
      canvas {
        display: block;
        width: 100%;
        height: auto;
        aspect-ratio: 4 / 3;
        background: #000;
        image-rendering: pixelated;
      }
    `
    this.canvas = document.createElement('canvas')
    shadow.append(style, this.canvas)
  }

  connectedCallback() {
    this.#maybeLoad()
  }

  disconnectedCallback() {
    this.#stopWatching()
  }

  attributeChangedCallback(name) {
    if (name === 'src') {
      this.#maybeLoad()
    }
  }

  #maybeLoad() {
    const src = this.getAttribute('src')

    // one instance per element, ever - re-pointing src needs a fresh element
    if (!src || !this.isConnected || this.loaded) {
      return
    }

    if (this.getAttribute('loading') === 'eager' || this.#inView()) {
      this.#stopWatching()
      this.#load(src)
      return
    }

    // A plain rect check on scroll, rather than an IntersectionObserver: an IO
    // silently delivers nothing in some embedding contexts, and "the cart just
    // never starts" is a much worse failure than a cheap scroll handler.
    if (!this.watching) {
      this.watching = () => this.#maybeLoad()
      addEventListener('scroll', this.watching, { passive: true })
      addEventListener('resize', this.watching, { passive: true })
    }
  }

  #stopWatching() {
    if (this.watching) {
      removeEventListener('scroll', this.watching)
      removeEventListener('resize', this.watching)
      this.watching = undefined
    }
  }

  // within a screen of the viewport, so it is running by the time it is looked at
  #inView() {
    const { top, bottom } = this.getBoundingClientRect()
    const margin = innerHeight
    return bottom > -margin && top < innerHeight + margin
  }

  #load(src) {
    this.loaded = true
    this.#stopWatching()
    this.dispatchEvent(new CustomEvent('null0-loading'))
    loadCart(src, this.canvas)
      .then((cart) => {
        this.cart = cart
        this.dispatchEvent(new CustomEvent('null0-loaded', { detail: cart }))
      })
      .catch((error) => {
        console.error(`null0-cart: could not load ${src}`, error)
        this.dispatchEvent(new CustomEvent('null0-error', { detail: error }))
      })
  }
}

customElements.define('null0-cart', Null0Cart)
