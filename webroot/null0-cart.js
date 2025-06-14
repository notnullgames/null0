// simpler web-component

import loadCart from './null0.js'

class Null0Cart extends HTMLElement {
  static get observedAttributes() {
    return ['src']
  }

  constructor() {
    super()
    const shadow = this.attachShadow({ mode: 'open' })
    this.canvas = document.createElement('canvas')
    shadow.appendChild(this.canvas)
  }

  connectedCallback() {}
  disconnectedCallback() {}

  attributeChangedCallback(name, oldValue, newValue) {
    if (name === 'src') {
      loadCart(newValue, this.canvas).then((cart) => {
        this.cart = cart
      })
    }
  }
}

customElements.define('null0-cart', Null0Cart)
