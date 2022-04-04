<template>
<div style="margin-bottom:0;">
<div :class="keyboardClass" >
</div>
</div>
</template>
<script>

import Keyboard from 'simple-keyboard';
import 'simple-keyboard/build/css/index.css';

export default {
  name: 'keyboard-component',
  props: {
    keyboardClass: {
      default: 'simple-keyboard',
      type: String,
    },
    input: {
      type: String,
    },
  },
  data: () => ({
    keyboard: null,
  }),
  mounted() {
    this.keyboard = new Keyboard(this.keyboardClass, {
      onChange: this.onChange,
      onKeyPress: this.onKeyPress,
      layout: {
        default: [
          'a z e r t y u i o p',
          'q s d f g h j k l m',
          '{enter} w x c v b n {bksp}',
        ],
      },
    });
  },
  methods: {
    onChange(input) {
      this.$emit('input', input);
    },
    onKeyPress(button) {
      this.$emit('keypress', button);
    },
  },
};

</script>

<style scoped>
ul {
  list-style-type: none;
  padding: 0;
}
li {
  display: inline-block;
  margin: 0 10px;
}
</style>
