<script setup>
import Keyboard from 'simple-keyboard';
import 'simple-keyboard/build/css/index.css';
import {onMounted, ref, defineEmits} from 'vue';

const emit = defineEmits(["onKeyPress"]);

const keyboard = ref(null);

const onKeyPress = (button) => {
  emit("onKeyPress", button)
}

onMounted(() => {
  keyboard.value = new Keyboard("simple-keyboard", {
    layout: {
      default: [
        'A Z E R T Y U I O P',
        'Q S D F G H J K L M',
        '{enter} W X C V B N {bksp}',
        ],
      },
      onKeyPress: onKeyPress,
  });
});
      
</script>
<template>
<div class="simple-keyboard" style="max-width:500px; margin:auto; margin-top:10%"></div>
</template>


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
